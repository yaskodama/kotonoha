#!/bin/sh
# 組み立て済みの公開用フォルダ（publish_local.sh が作る kotonoha/）をサーバに上げ、本番と手元が同じか確かめる
# 接続先は web/.deploy.env（git に入れない）に書く:
#   DEPLOY_HOST=…  DEPLOY_DIR=…（公開用フォルダの親。既定 ~/kodamay_org_site/kodamay.org）  DEPLOY_URL=https://…/kotonoha
# ユーザ名とパスワードは ~/.netrc の「machine $DEPLOY_HOST」から lftp が読む
set -e
HERE="$(cd "$(dirname "$0")" && pwd)"
[ -f "$HERE/.deploy.env" ] && . "$HERE/.deploy.env"
: "${DEPLOY_HOST:?web/.deploy.env に DEPLOY_HOST を書く}"
: "${DEPLOY_URL:?web/.deploy.env に DEPLOY_URL を書く}"
cd "${DEPLOY_DIR:-$HOME/kodamay_org_site/kodamay.org}"
lftp -e "set ssl:verify-certificate no; set net:timeout 20; set net:max-retries 2; cd public_html; mirror -R --no-perms kotonoha kotonoha; chmod 644 kotonoha/index.html kotonoha/app.js kotonoha/kotonoha.js kotonoha/samples.js kotonoha/flow.html kotonoha/flow.js; bye" "$DEPLOY_HOST"
UA="Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/130.0 Safari/537.36"
for f in index.html app.js kotonoha.js samples.js flow.html flow.js; do
  a=$(curl -s -A "$UA" "$DEPLOY_URL/$f" | shasum | cut -c1-12); b=$(shasum kotonoha/$f | cut -c1-12)
  [ "$a" = "$b" ] && echo "OK $f" || { echo "NG $f（本番と手元が違う）"; exit 1; }
done
