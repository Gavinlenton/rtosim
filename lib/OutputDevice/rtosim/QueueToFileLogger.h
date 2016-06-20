/* -------------------------------------------------------------------------- *
 * Copyright (c) 2010-2016 C. Pizzolato, M. Reggiani                          *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License");            *
 * you may not use this file except in compliance with the License.           *
 * You may obtain a copy of the License at:                                   *
 * http://www.apache.org/licenses/LICENSE-2.0                                 *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

#ifndef rtosim_QueueToFileLogger_h
#define rtosim_QueueToFileLogger_h

#include "rtosim/concurrency/Latch.h"
#include "rtosim/concurrency/Queue.h"
#include "rtosim/QueueData.h"
#include "rtosim/FileLogger.h"

namespace rtosim {

    template<typename DataType>
    class QueueToFileLogger {
    public:
        using FrameType = QueueData < DataType > ;
        using QueueType = rtosim::Concurrency::Queue < FrameType > ;
        QueueToFileLogger() = delete;
        QueueToFileLogger(const QueueToFileLogger<DataType>&) = delete;
        QueueToFileLogger& operator=(const QueueToFileLogger<DataType>&) = delete;

        QueueToFileLogger(
            QueueType& inputQueue,
            rtosim::Concurrency::Latch& subscriptionLatch,
            rtosim::Concurrency::Latch& readyToWriteLatch,
            const std::vector<std::string>& columnLabels,
            const std::string& outputDir,
            const std::string& filename,
            const std::string& extension = "sto");
        ~QueueToFileLogger() = default;
        void operator()();

    private:
        QueueType& inputQueue_;
        rtosim::Concurrency::Latch& subscriptionLatch_;
        rtosim::Concurrency::Latch& readyToWriteLatch_;
        FileLogger<DataType> logger_;
    };
}

#include "QueueToFileLogger.cpp"
#endif