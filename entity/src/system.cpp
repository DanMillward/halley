#include <chrono>
#include "system.h"
#include <iostream>

using namespace Halley;

Halley::System::System(std::initializer_list<FamilyBindingBase*> uninitializedFamilies, TimeLine tl)
	: families(uninitializedFamilies)
	, timeline(tl)
{
}

void Halley::System::onAddedToWorld(World& w) {
	this->world = &w;
	for (auto f : families) {
		f->bindFamily(w);
	}
}

void Halley::System::step(Time time) {
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	
	tick(time);
	
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end - start).count();
	nsTaken = static_cast<int>(duration);
}
