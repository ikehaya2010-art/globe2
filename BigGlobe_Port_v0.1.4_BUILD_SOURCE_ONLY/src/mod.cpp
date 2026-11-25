#include "ll/api/mod/NativeMod.h"
#include "ll/api/mod/RegisterHelper.h"

// This is only the LeviLamina native-mod lifecycle entry point.
// No world-generation hook is connected yet.
class BigGlobePortMod {
public:
    static BigGlobePortMod& getInstance() {
        static BigGlobePortMod instance;
        return instance;
    }

    bool load() {
        auto mod = ll::mod::NativeMod::current();
        if (mod) {
            mod->getLogger().info("BigGlobePort scaffold loaded (terrain hook not connected yet).");
        }
        return true;
    }

    bool enable() {
        auto mod = ll::mod::NativeMod::current();
        if (mod) {
            mod->getLogger().info("BigGlobePort enabled.");
        }
        return true;
    }

    bool disable() { return true; }
    bool unload() { return true; }
};

LL_REGISTER_MOD(BigGlobePortMod, BigGlobePortMod::getInstance());
