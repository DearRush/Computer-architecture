#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// include SSE intrinsics
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <x86intrin.h>
#endif


#define CLOCK_RATE_GHZ 2.26e9

static __inline__ uint64_t RDTSC()
{
    uint32_t hi, lo;
    __asm__ volatile
	(
		"rdtsc"
		: "=a"(lo), "=d"(hi)
	);
	return (((uint64_t)hi) << 32) | ((uint64_t)lo);
}

static int sum_naive(int n, int *a)
{
    int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}
	return sum;
}

static int sum_unrolled(int n, int *a)
{
    int sum = 0;

    // unrolled loop
	for (int i = 0; i < n / 4 * 4; i += 4)
    {
        sum += a[i+0];
        sum += a[i+1];
        sum += a[i+2];
        sum += a[i+3];

    }

    // tail case
	for (int i = n / 4 * 4; i < n; i++)
	{
		sum += a[i];
	}

    return sum;
}

static int sum_vectorized(int n, int *a)
{
    // WRITE YOUR VECTORIZED CODE HERE
	int result[4]={0};
	int sum=0;
	int uneven=n%4;
	__m128i ptr=_mm_setzero_si128();
	for(int i=0;i<n-4;i+=4)
	{
		ptr=_mm_add_epi32(ptr,_mm_loadu_si128(a+i));
	}
	_mm_storeu_si128(result,ptr);
	for(int i=0;i<uneven;i++)
	{
		result[i]+=a[n-uneven+i];
	}
	for(int i=0;i<4;i++)
	{
		sum+=result[i];
	}
	return sum;
}

static int sum_vectorized_unrolled(int n, int *a)
{
    // UNROLL YOUR VECTORIZED CODE HERE
	int result[4]={0};
	int sum=0;
	int uneven=n%16;
	__m128i ptr=_mm_setzero_si128();
	__m128i ptr1=_mm_setzero_si128();
	__m128i ptr2=_mm_setzero_si128();
	__m128i ptr3=_mm_setzero_si128();
	__m128i ptr4=_mm_setzero_si128();
	for(int i=0;i<n-16;i+=16)
	{
		ptr1=_mm_add_epi32(ptr1,_mm_loadu_si128(a+i));
		ptr2=_mm_add_epi32(ptr2,_mm_loadu_si128(a+i+4));
		ptr3=_mm_add_epi32(ptr3,_mm_loadu_si128(a+i+8));
		ptr4=_mm_add_epi32(ptr4,_mm_loadu_si128(a+i+12));
	}
	ptr=_mm_add_epi32(_mm_add_epi32(ptr1,ptr2),_mm_add_epi32(ptr3,ptr4));
	_mm_storeu_si128(result,ptr);
	for(int i=0;i<4;i++)
	{
		sum+=result[i];
	}
	for(int i=0;i<uneven;i++)
	{
		sum+=a[n-uneven+i];
	}
	return sum;
}

void benchmark(int n, int *a, int(*computeSum)(int, int*), char *name)
{
    // warm up cache
    int sum = computeSum(n, a);

    // measure
    uint64_t beginCycle = RDTSC();
    sum += computeSum(n, a);
	uint64_t cycles = RDTSC() - beginCycle;

    double microseconds = cycles/CLOCK_RATE_GHZ*1e6;

    // print results
	printf("%20s: ", name);
	if (sum == 2 * sum_naive(n, a))
	{
		printf("%.2f microseconds\n", microseconds);
	}
	else
	{
		printf("ERROR!\n");
	}
}

int main(int argc, char **argv)
{
    const int n = 9999;

    // initialize the array with random values
	srand48(time(NULL));
	int a[n] __attribute__((aligned(16)));
	for (int i = 0; i < n; i++)
	{
		a[i] = lrand48();
	}

    // benchmark series of codes
	benchmark(n, a, sum_naive, "naive");
	benchmark(n, a, sum_unrolled, "unrolled");
	benchmark(n, a, sum_vectorized, "vectorized");
	benchmark(n, a, sum_vectorized_unrolled, "vectorized unrolled");

    return 0;
}
