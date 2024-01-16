cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "id": "cordova-plugin-network-information.network",
        "file": "plugins/cordova-plugin-network-information/www/network.js",
        "pluginId": "cordova-plugin-network-information",
        "clobbers": [
            "navigator.connection"
        ]
    },
    {
        "id": "cordova-plugin-network-information.Connection",
        "file": "plugins/cordova-plugin-network-information/www/Connection.js",
        "pluginId": "cordova-plugin-network-information",
        "clobbers": [
            "Connection"
        ]
    },
    {
        "id": "cordova-plugin-networkinterface.networkinterface",
        "file": "plugins/cordova-plugin-networkinterface/www/networkinterface.js",
        "pluginId": "cordova-plugin-networkinterface",
        "clobbers": [
            "window.networkinterface"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "cordova-plugin-network-information": "3.0.0",
    "cordova-plugin-networkinterface": "2.0.0",
    "cordova-plugin-whitelist": "1.3.5"
};
// BOTTOM OF METADATA
});