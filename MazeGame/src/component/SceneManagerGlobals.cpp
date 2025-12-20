#include "../include/component/SceneManager.h"

// 在此翻译单元中定义全局实例与指针
// 其它文件包含 SceneManager.h 后可通过 extern 引用这两个符号
SceneManager sceneManager;
SceneManager* g_sceneManager = &sceneManager;