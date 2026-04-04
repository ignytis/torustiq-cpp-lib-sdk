#ifndef _TORUSTIQ_LIB_SDK_TYPEDEFS_H_
#define _TORUSTIQ_LIB_SDK_TYPEDEFS_H_

/** A structure returned by plugin to identify itself */
struct PluginId {
    const char *host_app = "torustiq";
    const unsigned int api_version;
};

/** Kind of plugin */
enum TorustiqPluginKind {
    TorustiqPluginKindStage,
    TorustiqPluginKindListener,
};

struct TorustiqPluginInfo {
    const char *id;
    const char *name;
    const TorustiqPluginKind kind;
};

/** A pointer to 'torustiq_plugin_get_info' function */
typedef const TorustiqPluginInfo (*TorustiqPluginGetInfoFnPtr)();

/** A pointer to 'torustiq_plugin_init' function */
typedef void (*TorustiqPluginInitFnPtr)();

struct TorustiqPlugin {
    TorustiqPluginInitFnPtr fn_init;
};

#endif  // _TORUSTIQ_LIB_SDK_TYPEDEFS_H_
