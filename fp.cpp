// fp.cpp
#include "fp.h"

fp::fp()
{
	;	// EMPTY
}

fp::~fp()
{
	;	// EMPTY
}

char *fp::myName(void)
{
	return "Yeonah Cho";
}

int fp::add(int a, int b)
{
	FPNumber fa(a);
	FPNumber fb(b);
	FPNumber result(0);

	// Put your code in here!

	if (fa.isNaN() == true || fb.isNaN() == true)
	{
		if (fa.isNaN() == true)
			result = a;
		else
			result = b;
	}

	else if (fa.isZero() == true || fb.isZero() == true)
	{
		if (fa.isZero() == true)
			result = b;
		else
			result = a;
	}

	else if (fa.isInfinity() == true && fb.isInfinity() == true)
	{
		if (fa.s() == fb.s())
			result = a;
		else
		{
			result.setS(1);
			result.setE(255);
			result.setF(12);
		}
	}

	else if (fa.isInfinity() == true || fb.isInfinity() == true)
	{
		if (fa.isInfinity() == true)
			result = a;
		else
			result = b;
	}

	else
	{
		long long t = 0;

		if (fa.s() == fb.s())
		{
			if (fa.e() > fb.e())
			{
				t = fa.f() + (fb.f() >> (fa.e() - fb.e()));
				fb.setE(fa.e());
			}
			else
			{
				t = fb.f() + (fa.f() >> (fb.e() - fa.e()));
				fa.setE(fb.e());
			}

			if (((t >> 26) & 1) == 1)
			{
				t = t >> 1;
				fa.setE(fa.e() + 1);

				if (fa.e() == 255)
				{
					result.setS(fa.s());
					result.setE(255);
					result.setF(0);
				}
			}

			else if (((t >> 25) & 1) == 0)
			{
				t = t << 1;
				fa.setE(fa.e() - 1);

				if (fa.e() == 0)
				{
					t = t >> 1;
					result.setS(fa.s());
					result.setE(fa.e());
					result.setF(t);
				}
			}

			else
			{
				result.setS(fa.s());
				result.setE(fa.e());
				result.setF(t);
			}
		}
	}

	return result.asInt();
}

int fp::mul(int a, int b)
{
	FPNumber fa(a);
	FPNumber fb(b);
	FPNumber result(0);

	// Put your code in here!

	if (fa.isNaN() == true || fb.isNaN() == true)
	{
		if (fa.isNaN() == true)
			result = a;
		else
			result = b;
	}

	else if ((fa.isZero() == true || fb.isZero() == true) &&
				(fa.isInfinity() == true || fb.isInfinity() == true))
	{
		result.setS(1);
		result.setE(255);
		result.setF(12);
	}

	else if (fa.isZero() == true || fb.isZero() == true)
	{
		fa.setS(fa.s() ^ fb.s());
	}

	else if (fa.isInfinity() == true || fb.isInfinity() == true)
	{
		result.setS(fa.s() ^ fb.s());
		result.setE(255);
		result.setF(0);
	}

	else
	{
		result.setS(fa.s() ^ fb.s());
		result.setE(fa.e() + fb.e() - 127);

		if (result.e() > 254)
		{
			result.setS(fa.s() ^ fb.s());
			result.setE(255);
			result.setF(0);
		}
		else if (result.e() < 0)
		{
			result.setS(fa.s() ^ fb.s());
			result.setE(0);
			result.setF(0);
		}

		long long t = 0;

		t = fa.f() * fb.f();

		if (((t >> 26) & 1) == 1)
		{
			t = t >> 1;
			fa.setE(fa.e() + 1);

			if (fa.e() == 255)
			{
				result.setS(fa.s());
				result.setE(255);
				result.setF(0);
			}
		}

		else if (((t >> 25) & 1) == 0)
		{
			t = t << 1;
			fa.setE(fa.e() - 1);

			if (fa.e() == 0)
			{
				t = t >> 1;
				result.setS(fa.s());
				result.setE(fa.e());
				result.setF(t);
			}
		}

		else
		{
			result.setS(fa.s());
			result.setE(fa.e());
			result.setF(t);
		}

	}

	return result.asInt();
}
