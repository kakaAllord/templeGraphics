#include "tgpch.h"
#include "Log.h"

int main()
{
	templeG::Log::Init();
	TG_TRACE("templeGraphics!!");
	TG_INFO("templeGraphics!!");
	TG_WARN("templeGraphics!!");
	TG_ERROR("templeGraphics!!");
	TG_CRITICAL("templeGraphics!!");
	while (!false);
	return 0;
}