/**********************************************************************************************************************
 * Copyright (c) Prophesee S.A.                                                                                       *
 *                                                                                                                    *
 * Licensed under the Apache License, Version 2.0 (the "License");                                                    *
 * you may not use this file except in compliance with the License.                                                   *
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0                                 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed   *
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.                      *
 * See the License for the specific language governing permissions and limitations under the License.                 *
 **********************************************************************************************************************/

#ifndef METAVISION_HAL_FUTURE_SAMPLE_DECODER_H
#define METAVISION_HAL_FUTURE_SAMPLE_DECODER_H

#include <metavision/hal/facilities/future/i_decoder.h>

namespace Future {

/// @brief Interface for decoding events.
///
/// This class is the implementation of HAL's facility @ref Metavision::Future::I_Decoder
/// The implementation must have the following feature :
///
/// - support of time shifting : If enabled, the timestamp of the decoded events will be shifted of the value of the
///   time of the first event
class SampleDecoder : public Metavision::Future::I_Decoder {
public:
    /// @brief Constructor
    ///
    /// @param time_shifting_enabled If true, the timestamp of the decoded events will be shifted of the value of the
    /// time of the first event
    SampleDecoder(bool do_time_shift,
                  const std::shared_ptr<Metavision::I_EventDecoder<Metavision::EventCD>> &cd_event_decoder);

    /// @brief Gets the timestamp of the last event
    ///
    /// @return Timestamp of the last event
    Metavision::timestamp get_last_timestamp() const override final;

    /// @brief Finds the timestamp shift
    ///
    /// If the timestamp shift (timestamp of the first timer high event in the stream) is already known,
    /// the function returns true and the parameter @p timestamp_shift will be set to its value.
    /// Otherwise, the function returns false and does nothing.
    /// @return true if the timestamp shift is already known, false otherwise
    bool get_timestamp_shift(Metavision::timestamp &timestamp_shift) const override final;

    /// @brief Gets size (byte) of raw event
    uint8_t get_raw_event_size_bytes() const override final;

    /// @brief Resets the decoder last timestamp
    /// @param timestamp Timestamp to reset the decoder to
    /// @return True if the reset operation could complete, false otherwise.
    /// @note It is expected after this call has succeeded, that @ref get_last_timestamp returns @p timestamp
    /// @warning If time shifting is enabled, the @p timestamp must be in the shifted time reference
    bool reset_timestamp(const Metavision::timestamp &timestamp) override final;

    /// @brief Resets the decoder timestamp shift
    /// @param shift Timestamp shift to reset the decoder to
    /// @return True if the reset operation could complete, false otherwise.
    /// @note If time shifting is disabled, this function does nothing and returns false
    bool reset_timestamp_shift(const Metavision::timestamp &shift) override final;

private:
    /// @brief Decodes raw data.
    ///
    /// Identifies the events in the buffer and dispatches it to the instance of @ref Metavision::I_EventDecoder
    /// corresponding to each event type.
    /// @warning It is mandatory to pass strictly consecutive buffers from the same source to this method
    ///
    /// @param ev Pointer on first event
    /// @param evend Pointer after the last event
    void decode_impl(const RawData *const ev, const RawData *const evend) override final;

    Metavision::timestamp last_timestamp_{0};
    Metavision::timestamp time_shift_{0};
    bool time_shift_set_{false};
};

} // namespace Future

#endif // METAVISION_HAL_FUTURE_SAMPLE_DECODER_H
