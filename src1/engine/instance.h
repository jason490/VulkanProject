#pragma once

// namespace for createion functions/definitions
namespace vkInit {
    vk::Instance make_instance(bool debug, const char* applicationName) {
        if (debug) {
            std::cout << "Making an instance...\n";
        }

        uint32_t version { 0 };
        vkEnumerateInstanceVersion(&version);
        if (debug) {
            std::cout << "System can support vulkan variant: " << VK_API_VERSION_VARIANT(version)
                << ", Major: " << VK_API_VERSION_MAJOR(version)
                << ", Minor: " << VK_API_VERSION_MINOR(version)
                << ", Patch: " << VK_API_VERSION_PATCH(version) << '\n';
        }

        version &= ~(0xFFFU); // set the patch to 0 for best compatibility/stability
        //             ^^^       lower 12 bytes are patch

        // or use VK_MAKE_API_VERSION(variant, major, minor, patch)
        version = VK_MAKE_API_VERSION(0, 1, 0, 0);

        vk::ApplicationInfo appInfo = vk::ApplicationInfo(
            applicationName,
            version,
            "text",
            version,
            version
        );

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (debug) {
            std::cout << "Extensions to be requested: \n";
            for (const char* extensionName : extensions) {
                std::cout << "\t\"" << extensionName << "\"\n";
            }
        }
        

        vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
            vk::InstanceCreateFlags().
            &appInfo,
            0, nullptr, // enabled layers
            static_cast<uint32_t>(extension.size()), extensions,data() // enabled extensions
        );

        try {
            return vk::createInstance(createInfo, nullptr);
        }
        catch (vk::SystemError err) {
            if (debug) {
                std::cout << "Failed: create instance"
            }
        }

        if (debug) {
            std::cout << "Success: instance creation"
        }

        return nullptr;
    }
}