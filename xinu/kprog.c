/* kprog.c - ことのはから k2xinu.mjs で生成。手で直さないこと */
/* 元: Xinuの挨拶.txt */
#include <xinu.h>
#include "krt.h"

struct kclass kcls0;
struct kclass kcls1;

static void kinit0(struct kact *self) {
	self->f[2] = kn(0);
}

static void kh0_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	L[0] = arg;
	{ kv v = kget(kread(L[0], "指示"), kn(1), "指示の 1 番目");
	  self->f[0] = v;
	}
	{ kv v = kget(kread(L[0], "指示"), kn(2), "指示の 2 番目");
	  self->f[1] = v;
	}
	{ kv v = kget(kread(L[0], "指示"), kn(3), "指示の 3 番目");
	  self->f[3] = v;
	}
	{ kv a = knone();
	  ksend(kactv(self), "挨拶", a, 0);
	}
}

static void kh0_1(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	self->f[2] = kadd(self->f[2], kn(1), "済んだ回数");
	{ static const int32 lit[7] = { 1, 0, 1, 0, 1, 0, 1 };
	  kv vals[7];
	  vals[0] = ks("[");
	  vals[1] = self->f[0];
	  vals[2] = ks("] hello from Xinu! (");
	  vals[3] = self->f[2];
	  vals[4] = ks("/");
	  vals[5] = self->f[1];
	  vals[6] = ks(")");
	  kdisp(7, lit, vals); }
	if (klt(self->f[2], self->f[1], "済んだ回数", "回数")) {
		{ kv a = knone();
		  ksend(kactv(self), "挨拶", a, 0);
		}
	} else {
		{ kv a = knone();
		  ksend(self->f[3], "終わった", a, 0);
		}
	}
}

static const char *kf0[] = { "呼び名", "回数", "済んだ回数", "報告先" };
static const struct khent kht0[] = { { "始め", kh0_0 }, { "挨拶", kh0_1 } };
struct kclass kcls0 = { "挨拶係", 4, kf0, kinit0, 2, kht0, 0 };

static void kinit1(struct kact *self) {
	self->f[0] = kn(0);
}

static void kh1_0(struct kact *self, kv arg) {
	kv L[1];
	int32 i;
	(void)L;
	for (i = 0; i < 1; i++) L[i].t = KN_UNSET;
	self->f[0] = kadd(self->f[0], kn(1), "報告数");
	if (keq(self->f[0], kn(2))) {
		{ static const int32 lit[1] = { 1 };
		  kv vals[1];
		  vals[0] = ks("=== Sample finished, starting shell ===");
		  kdisp(1, lit, vals); }
	}
}

static const char *kf1[] = { "報告数" };
static const struct khent kht1[] = { { "終わった", kh1_0 } };
struct kclass kcls1 = { "見届け係", 1, kf1, kinit1, 1, kht1, 0 };

static void kbody(void) {
	struct kact *self = NULL; (void)self;
	kv L[5];
	int32 i;
	(void)L;
	for (i = 0; i < 5; i++) L[i].t = KN_UNSET;
	{ static const int32 lit[1] = { 1 };
	  kv vals[1];
	  vals[0] = ks("=== Sample: two greeter processes running concurrently ===");
	  kdisp(1, lit, vals); }
	L[0] = knew(&kcls1);
	L[1] = knew(&kcls0);
	L[2] = knew(&kcls0);
	L[3] = knewarr();
	{ kv arr = kread(L[3], "甲の指示");
	  kpush(arr, ks("Alice"), "甲の指示");
	  kpush(arr, kn(3), "甲の指示");
	  kpush(arr, kread(L[0], "見届け役"), "甲の指示");
	}
	{ kv a = kread(L[3], "甲の指示");
	  ksend(kread(L[1], "甲"), "始め", a, 1);
	}
	L[4] = knewarr();
	{ kv arr = kread(L[4], "乙の指示");
	  kpush(arr, ks("Bob"), "乙の指示");
	  kpush(arr, kn(3), "乙の指示");
	  kpush(arr, kread(L[0], "見届け役"), "乙の指示");
	}
	{ kv a = kread(L[4], "乙の指示");
	  ksend(kread(L[2], "乙"), "始め", a, 1);
	}
}

void kotonoha_main(void) { krun(kbody); }
