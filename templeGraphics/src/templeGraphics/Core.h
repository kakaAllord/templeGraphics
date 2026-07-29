#pragma once

#define TG_ASSERT(x, ...) { if(!(x)) { TG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
