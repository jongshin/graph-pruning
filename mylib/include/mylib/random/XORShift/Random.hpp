#pragma once

#include <random>
#include <functional>

#include "XORShift.hpp"

#if defined(__MINGW32__)
inline XORShift32& getEngine() {
	static XORShift32 engine(rd());
	return engine;
}
#else
inline XORShift32& getEngine() {
	std::random_device rd;
static 	XORShift32 engine(rd());
	return engine;
}
#endif

template <typename Dist = std::uniform_real_distribution<double>, typename Engine = XORShift32>
class Ran {
public :
	Ran(Dist dist, Engine& engine = getEngine())
		: distribution(std::move(dist))
		, engine(engine)
	{}

	template <typename... Args>
	Ran(Args&&... args)
		: distribution(std::forward<Args>(args)...)
		, engine(getEngine())
	{}

	double operator()() {
		return distribution(engine);
	}
private :
	Dist distribution;
	Engine& engine;
};

typedef Ran<std::uniform_int_distribution<int>> RInt;
typedef Ran<std::uniform_real_distribution<double>> RDouble;
typedef Ran<std::normal_distribution<double>> RGaussian;
typedef Ran<std::exponential_distribution<double>> RExp;
typedef Ran<std::poisson_distribution<int>> RPoisson;
typedef Ran<std::binomial_distribution<int>> RBinomial;


