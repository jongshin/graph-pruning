#pragma once

class XORShift32 {
	public:
		typedef uint32_t result_type;

	public:
		XORShift32(uint32_t seed = defaultSeed)
		: x(seed) {
		}

		result_type operator()() {
			uint32_t t = x ^ (x << 11);
			x = y; y = z; z = w;
			return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
		}

		static constexpr result_type min() {
			return 1;
		}

		static constexpr result_type max() {
			return std::numeric_limits<uint32_t>::max();
		}

	private:
		static const uint32_t defaultSeed = 13579;

	private:
		uint32_t x;
		uint32_t y = 362436069;
		uint32_t z = 521288629;
		uint32_t w = 88675123;
};

/*
 * TODO: Native 64bit algorithm?
 */
class XORShift64 {
	public:
		typedef uint64_t result_type;

	public:
		XORShift64(uint64_t val = defaultSeed)
		: x1(static_cast<uint32_t>(val)), x2(static_cast<uint32_t>(val >> 32)) {
		}

		result_type operator()() {
			return ((uint64_t) x1()) << 32 | x2();
		}

		static constexpr result_type min() {
			return 1;
		}

		static constexpr result_type max() {
			return std::numeric_limits<uint64_t>::max();
		}

	private:
		static const uint64_t defaultSeed = 135790135790L;

	private:
		XORShift32 x1;
		XORShift32 x2;
};

