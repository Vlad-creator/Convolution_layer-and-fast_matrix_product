#include "Convolutions_h/Conv_naiv.h"
#include "Convolutions_h/Conv_fast.h"
#include "Convolutions_h/Conv_GEMM.h"
#include <chrono>
#include <thread>
#include <ratio>

using namespace matrix;
using namespace Tensor;

int main()
{

	uint64_t duration_normal = 0;
	uint64_t duration_fast = 0;
	uint64_t duration_GEMM = 0;

	Tensor4 test(1 , 3 , 100 , 50 , 0);
	Tensor4 filter(16 , 3 , 4 , 4 , 0);
	for (int i = 0 ; i < 5 ; ++i)
	{
		auto t1 = std::chrono::high_resolution_clock::now();
		Tensor4 res_1 = convolution_layer_naive(test , filter);
		auto t2 = std::chrono::high_resolution_clock::now();
		duration_normal += std::chrono::duration_cast<std::chrono::milliseconds> (t2 - t1).count();

		auto t3 = std::chrono::high_resolution_clock::now();
		Tensor4 res_2 = conv_layer_fast(test , filter);
		auto t4 = std::chrono::high_resolution_clock::now();
		duration_fast += std::chrono::duration_cast<std::chrono::milliseconds> (t4 - t3).count();

		auto t5 = std::chrono::high_resolution_clock::now();
		Tensor4 res_3 = conv_layer_GEMM(test , filter);
		auto t6 = std::chrono::high_resolution_clock::now();
		duration_GEMM += std::chrono::duration_cast<std::chrono::milliseconds> (t6 - t5).count();

		assert(res_1 == res_2);
		assert(res_1 == res_3);
	}

	std::cout << "Normal conv - " << duration_normal << " - milliseconds" << std::endl;
	std::cout << "Fast conv   - " << duration_fast << " - milliseconds" << std::endl;
	std::cout << "GEMM conv   - " << duration_GEMM << " - milliseconds" << std::endl;

	//std::cout << "test\n" << test << std::endl;
	//std::cout << "filter\n" << filter << std::endl;
	//std::cout << "res_1\n" << res_1 << std::endl;
	//std::cout << "res_2\n" << res_2 << std::endl;

	return 0;
}