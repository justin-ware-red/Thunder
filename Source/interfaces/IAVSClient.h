/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "Module.h"

namespace WPEFramework {
namespace Exchange {

    //@json
    struct IAVSController : virtual public Core::IUnknown {
        enum { ID = ID_AVSCONTROLLER };
        virtual ~IAVSController(){}

        //@event
        struct INotification : virtual public Core::IUnknown {
            enum { ID = ID_AVSCONTROLLER_NOTIFICATION };
            virtual ~INotification(){}

            enum dialoguestate {
                IDLE,
                LISTENING,
                EXPECTING,
                THINKING,
                SPEAKING
            };

            /// @brief notifies about dialogue state changes
            /// @param state The new state (e.g. SPEAKING)
            virtual void DialogueStateChange(const dialoguestate state) = 0;
        };

        virtual void Register(INotification* sink) = 0;
        virtual void Unregister(const INotification* sink) = 0;

        /// @brief Mutes the audio output of AVS
        /// @param mute Mute or umute (e.g. true)
        /// @retval ERROR_GENERAL when there is a fatal error or authorisation is not possible
        virtual uint32_t Mute(const bool mute) = 0;

        /// @brief Starts or stops the voice recording, skipping keyword detection
        /// @param start Start or stop voice recording (e.g. true)
        /// @retval ERROR_GENERAL when there is a fatal error or authorisation is not possible
        virtual uint32_t Record(const bool start) = 0;
    };

    struct IAVSClient : virtual public Core::IUnknown {
        enum { ID = ID_AVSCLIENT };

        virtual ~IAVSClient(){};

        virtual bool Initialize(PluginHost::IShell* service, const std::string& alexaClientConfig,
            const std::string& smartScreenConfig, const std::string& pathToInputFolder, const std::string& audioSource,
            const bool enableKWD, const std::string& logLevel) = 0;
        virtual bool Deinitialize() = 0;
        virtual IAVSController* Controller() = 0;
        virtual void StateChange(PluginHost::IShell* audioSource) = 0;
    };

} // Exchange
} // WPEFramework
