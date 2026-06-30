#ifndef _TORUSTIQ_LIB_SDK_TYPEDEFS_H_
#define _TORUSTIQ_LIB_SDK_TYPEDEFS_H_

#include <stdint.h>
#include <stdlib.h>

extern "C" struct TorustiqPluginInfo {
    const char* host_app = "torustiq";
    const unsigned int api_version;

    const char* id;
    const char* name;
};

enum TorustiqMessageType {
    /**
     * Regular data message.
     */
    TORUSTIQ_MESSAGE_TYPE_DATA,
    /**
     * Send when end of data is reached.
     */
    TORUSTIQ_MESSAGE_TYPE_EOF,
};

extern "C" struct TorustiqMessageHeader {
    const char* key;
    const char* value;
};

extern "C" struct TorustiqMessage {
    const TorustiqMessageType type;
    const size_t payload_size;
    const uint8_t* payload;
    const size_t headers_count;
    const TorustiqMessageHeader* headers;
};

enum TorustiqPluginStageKind {
    TORUSTIQ_PLUGIN_STAGE_KIND_SOURCE,
    TORUSTIQ_PLUGIN_STAGE_KIND_PROCESSOR,
    TORUSTIQ_PLUGIN_STAGE_KIND_SINK,
};

/** A handle to a stage instance */
typedef unsigned int TorustiqPluginStageHandle;

/**
 * torustiq_plugin_get_info function
 * Returns the general information about plugin which helps the host
 * application to validate the plugin and its compatibility
 */
typedef const TorustiqPluginInfo (*TorustiqPluginGetInfoFnPtr)();

struct CreateNewStageFnArgs {
    TorustiqPluginStageKind stageKind;
};
/**
 * torustiq_plugin_create_new_stage function
 * This function is expected to allocate resources for a new stage
 * and return handle to this new instance. The host application will
 * use this handle to operate with stage instance.
 */
typedef TorustiqPluginStageHandle (*TorustiqPluginCreateNewStageFnPtr)(CreateNewStageFnArgs args);

/**
 * torustiq_plugin_stage_start function
 * Starts the stage processing. Usually it includes some preparation like opening
 * files or sockets and then an infinite loop which processes the data
 */
typedef void (*TorustiqPluginStageStartFnPtr)(TorustiqPluginStageHandle stageHandle);

/**
 * torustiq_plugin_set_config_value function
 * Sets a value for stage confiuguration key.
 */
typedef void (*TorustiqPluginSetConfigValueFnPtr)(TorustiqPluginStageHandle stageHandle, const char *key, const char *value);

extern "C" struct TorustiqPlugin {
    // Should init be called separately from the rest?
    // TorustiqPluginInitFnPtr             fn_init;
    TorustiqPluginCreateNewStageFnPtr   fn_create_new_stage;
    TorustiqPluginSetConfigValueFnPtr   fn_set_config_value;
    TorustiqPluginStageStartFnPtr       fn_stage_start;
};

/**
 * This function is called from modules to enqueue a message to the pipeline.
 */
typedef void (*TorustiqHostSendMessageFnPtr)(TorustiqPluginStageHandle, const TorustiqMessage*);

/**
 * Globals shared with plugin by host
 */
struct TorustiqHostGlobals {
    TorustiqHostSendMessageFnPtr sendMessageFnPtr;
};

/**
 * torustiq_plugin_init function
 * Initializes the plugin.
 * NB: this is about initializing the general plugin configuration
 * which could be shared between stages
 */
typedef const TorustiqPlugin (*TorustiqPluginInitFnPtr)(TorustiqHostGlobals globals);

#endif  // _TORUSTIQ_LIB_SDK_TYPEDEFS_H_
