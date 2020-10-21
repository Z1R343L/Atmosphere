/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <vapours.hpp>

namespace ams::sdmmc::impl {

    struct SdHostStandardRegisters {
        volatile uint32_t dma_address;
        volatile uint16_t block_size;
        volatile uint16_t block_count;
        volatile uint32_t argument;
        volatile uint16_t transfer_mode;
        volatile uint16_t command;
        volatile uint32_t response[0x4];
        volatile uint32_t buffer;
        volatile uint32_t present_state;
        volatile uint8_t host_control;
        volatile uint8_t power_control;
        volatile uint8_t block_gap_control;
        volatile uint8_t wake_up_control;
        volatile uint16_t clock_control;
        volatile uint8_t timeout_control;
        volatile uint8_t software_reset;
        volatile uint16_t normal_int_status;
        volatile uint16_t error_int_status;
        volatile uint16_t normal_int_enable;
        volatile uint16_t error_int_enable;
        volatile uint16_t normal_signal_enable;
        volatile uint16_t error_signal_enable;
        volatile uint16_t acmd12_err;
        volatile uint16_t host_control2;
        volatile uint32_t capabilities;
        volatile uint32_t capabilities_1;
        volatile uint32_t max_current;
        volatile uint32_t _0x4c;
        volatile uint16_t set_acmd12_error;
        volatile uint16_t set_int_error;
        volatile uint8_t adma_error;
        volatile uint8_t _0x56[0x3];
        volatile uint32_t adma_address;
        volatile uint32_t upper_adma_address;
        volatile uint16_t preset_for_init;
        volatile uint16_t preset_for_default;
        volatile uint16_t preset_for_high;
        volatile uint16_t preset_for_sdr12;
        volatile uint16_t preset_for_sdr25;
        volatile uint16_t preset_for_sdr50;
        volatile uint16_t preset_for_sdr104;
        volatile uint16_t preset_for_ddr50;
        volatile uint32_t _0x70[0x23];
        volatile uint16_t slot_int_status;
        volatile uint16_t host_version;

        static constexpr inline u16 BlockCountMax = 0xFFFF;
    };
    static_assert(sizeof(SdHostStandardRegisters) == 0x100);

    constexpr inline size_t SdmaBufferBoundary = 512_KB;

    #define SD_REG_BITS_MASK(NAME)                                      REG_NAMED_BITS_MASK    (SD_HOST_STANDARD, NAME)
    #define SD_REG_BITS_VALUE(NAME, VALUE)                              REG_NAMED_BITS_VALUE   (SD_HOST_STANDARD, NAME, VALUE)
    #define SD_REG_BITS_ENUM(NAME, ENUM)                                REG_NAMED_BITS_ENUM    (SD_HOST_STANDARD, NAME, ENUM)
    #define SD_REG_BITS_ENUM_SEL(NAME, __COND__, TRUE_ENUM, FALSE_ENUM) REG_NAMED_BITS_ENUM_SEL(SD_HOST_STANDARD, NAME, __COND__, TRUE_ENUM, FALSE_ENUM)

    #define DEFINE_SD_REG(NAME, __OFFSET__, __WIDTH__)                                                                                                                  REG_DEFINE_NAMED_REG           (SD_HOST_STANDARD, NAME, __OFFSET__, __WIDTH__)
    #define DEFINE_SD_REG_BIT_ENUM(NAME, __OFFSET__, ZERO, ONE)                                                                                                         REG_DEFINE_NAMED_BIT_ENUM      (SD_HOST_STANDARD, NAME, __OFFSET__, ZERO, ONE)
    #define DEFINE_SD_REG_TWO_BIT_ENUM(NAME, __OFFSET__, ZERO, ONE, TWO, THREE)                                                                                         REG_DEFINE_NAMED_TWO_BIT_ENUM  (SD_HOST_STANDARD, NAME, __OFFSET__, ZERO, ONE, TWO, THREE)
    #define DEFINE_SD_REG_THREE_BIT_ENUM(NAME, __OFFSET__, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN)                                                               REG_DEFINE_NAMED_THREE_BIT_ENUM(SD_HOST_STANDARD, NAME, __OFFSET__, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN)
    #define DEFINE_SD_REG_FOUR_BIT_ENUM(NAME, __OFFSET__, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE, THIRTEEN, FOURTEEN, FIFTEEN) REG_DEFINE_NAMED_FOUR_BIT_ENUM (SD_HOST_STANDARD, NAME, __OFFSET__, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, TWELVE, THIRTEEN, FOURTEEN, FIFTEEN)

    DEFINE_SD_REG(BLOCK_SIZE_TRANSFER_BLOCK_SIZE, 0, 12);
    DEFINE_SD_REG_THREE_BIT_ENUM(BLOCK_SIZE_SDMA_BUFFER_BOUNDARY, 12, FOUR_KB, EIGHT_KB, SIXTEEN_KB, THIRTY_TWO_KB, SIXTY_FOUR_KB, ONE_TWENTY_EIGHT_KB, TWO_FIFTY_SIX_KB, FIVE_TWELVE_KB);
    constexpr inline size_t SdHostStandardBlockSizeTransferBlockSizeMax = 0xFFF;

    DEFINE_SD_REG_BIT_ENUM(TRANSFER_MODE_DMA_ENABLE,              0, DISABLE, ENABLE);
    DEFINE_SD_REG_BIT_ENUM(TRANSFER_MODE_BLOCK_COUNT_ENABLE,      1, DISABLE, ENABLE);
    DEFINE_SD_REG_TWO_BIT_ENUM(TRANSFER_MODE_AUTO_CMD_ENABLE,     2, DISABLE, CMD12_ENABLE, CMD23_ENABLE, AUTO_SELECT);
    DEFINE_SD_REG_BIT_ENUM(TRANSFER_MODE_DATA_TRANSFER_DIRECTION, 4, WRITE, READ);
    DEFINE_SD_REG_BIT_ENUM(TRANSFER_MODE_MULTI_BLOCK_SELECT,      5, SINGLE_BLOCK, MULTI_BLOCK);

    DEFINE_SD_REG_TWO_BIT_ENUM(COMMAND_RESPONSE_TYPE, 0, NO_RESPONSE, RESPONSE_LENGTH_136, RESPONSE_LENGTH_48, RESPONSE_LENGTH_48_CHECK_BUSY_AFTER_RESPONSE);
    DEFINE_SD_REG_BIT_ENUM(COMMAND_CRC_CHECK,         3, DISABLE, ENABLE);
    DEFINE_SD_REG_BIT_ENUM(COMMAND_INDEX_CHECK,       4, DISABLE, ENABLE);
    DEFINE_SD_REG_BIT_ENUM(COMMAND_DATA_PRESENT,      5, NO_DATA_PRESENT, DATA_PRESENT);
    DEFINE_SD_REG(COMMAND_COMMAND_INDEX, 8, 6);
    constexpr inline size_t SdHostStandardCommandIndexMax = 0x3F;

    DEFINE_SD_REG_BIT_ENUM(PRESENT_STATE_COMMAND_INHIBIT_CMD,     0, READY, NOT_READY);
    DEFINE_SD_REG_BIT_ENUM(PRESENT_STATE_COMMAND_INHIBIT_DAT,     1, READY, NOT_READY);
    DEFINE_SD_REG_BIT_ENUM(PRESENT_STATE_DAT0_LINE_SIGNAL_LEVEL, 20, LOW, HIGH);
    DEFINE_SD_REG_BIT_ENUM(PRESENT_STATE_DAT1_LINE_SIGNAL_LEVEL, 21, LOW, HIGH);
    DEFINE_SD_REG_BIT_ENUM(PRESENT_STATE_DAT2_LINE_SIGNAL_LEVEL, 22, LOW, HIGH);
    DEFINE_SD_REG_BIT_ENUM(PRESENT_STATE_DAT3_LINE_SIGNAL_LEVEL, 23, LOW, HIGH);

    DEFINE_SD_REG_BIT_ENUM(HOST_CONTROL_DATA_TRANSFER_WIDTH,          1, ONE_BIT, FOUR_BIT);
    DEFINE_SD_REG_BIT_ENUM(HOST_CONTROL_HIGH_SPEED_ENABLE,            2, NORMAL_SPEED, HIGH_SPEED);
    DEFINE_SD_REG_TWO_BIT_ENUM(HOST_CONTROL_DMA_SELECT,               3, SDMA, RESERVED1, ADMA2, ADMA2_OR_ADMA3);
    DEFINE_SD_REG_BIT_ENUM(HOST_CONTROL_EXTENDED_DATA_TRANSFER_WIDTH, 5, USE_DATA_TRANSFER_WIDTH, EIGHT_BIT);

    DEFINE_SD_REG_BIT_ENUM(POWER_CONTROL_SD_BUS_POWER_FOR_VDD1, 0, OFF, ON);
    DEFINE_SD_REG_THREE_BIT_ENUM(POWER_CONTROL_SD_BUS_VOLTAGE_SELECT_FOR_VDD1, 1, RESERVED0, RESERVED1, RESERVED2, RESERVED3, RESERVED4, 1_8V, 3_0V, 3_3V);

    DEFINE_SD_REG_BIT_ENUM(CLOCK_CONTROL_SD_CLOCK_ENABLE, 2, DISABLE, ENABLE);

    DEFINE_SD_REG_BIT_ENUM(SOFTWARE_RESET_FOR_ALL, 0, WORK, RESET);
    DEFINE_SD_REG_BIT_ENUM(SOFTWARE_RESET_FOR_CMD, 1, WORK, RESET);
    DEFINE_SD_REG_BIT_ENUM(SOFTWARE_RESET_FOR_DAT, 2, WORK, RESET);

    DEFINE_SD_REG_BIT_ENUM(NORMAL_INTERRUPT_STATUS_COMMAND_COMPLETE,   0, NOT_COMPLETE, COMPLETE);
    DEFINE_SD_REG_BIT_ENUM(NORMAL_INTERRUPT_STATUS_TRANSFER_COMPLETE,  1, NOT_COMPLETE, COMPLETE);
    DEFINE_SD_REG_BIT_ENUM(NORMAL_INTERRUPT_STATUS_DMA_INTERRUPT,      3, NOT_GENERATED, GENERATED);
    DEFINE_SD_REG_BIT_ENUM(NORMAL_INTERRUPT_STATUS_ERROR_INTERRUPT,   15, NO_ERROR, ERROR);

    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_COMMAND_TIMEOUT,  0, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_COMMAND_CRC,      1, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_COMMAND_END_BIT,  2, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_COMMAND_INDEX,    3, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_DATA_TIMEOUT,     4, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_DATA_CRC,         5, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_DATA_END_BIT,     6, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_AUTO_CMD,         8, NO_ERROR, ERROR);

    DEFINE_SD_REG_BIT_ENUM(AUTO_CMD_ERROR_AUTO_CMD_TIMEOUT,  1, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(AUTO_CMD_ERROR_AUTO_CMD_CRC,      2, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(AUTO_CMD_ERROR_AUTO_CMD_END_BIT,  3, NO_ERROR, ERROR);
    DEFINE_SD_REG_BIT_ENUM(AUTO_CMD_ERROR_AUTO_CMD_INDEX,    4, NO_ERROR, ERROR);

    DEFINE_SD_REG_BIT_ENUM(NORMAL_INTERRUPT_STATUS_ENABLE_COMMAND_COMPLETE,  0, MASKED, ENABLED);
    DEFINE_SD_REG_BIT_ENUM(NORMAL_INTERRUPT_STATUS_ENABLE_TRANSFER_COMPLETE, 1, MASKED, ENABLED);

    #define SD_HOST_STANDARD_NORMAL_INTERRUPT_ENABLE_ISSUE_COMMAND(__ENUM__)          \
        SD_REG_BITS_ENUM(NORMAL_INTERRUPT_STATUS_ENABLE_COMMAND_COMPLETE,  __ENUM__), \
        SD_REG_BITS_ENUM(NORMAL_INTERRUPT_STATUS_ENABLE_TRANSFER_COMPLETE, __ENUM__)

    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_COMMAND_TIMEOUT_ERROR,  0, MASKED, ENABLED);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_COMMAND_CRC_ERROR,      1, MASKED, ENABLED);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_COMMAND_END_BIT_ERROR,  2, MASKED, ENABLED);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_COMMAND_INDEX_ERROR,    3, MASKED, ENABLED);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_DATA_TIMEOUT_ERROR,     4, MASKED, ENABLED);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_DATA_CRC_ERROR,         5, MASKED, ENABLED);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_DATA_END_BIT_ERROR,     6, MASKED, ENABLED);
    DEFINE_SD_REG_BIT_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_AUTO_CMD_ERROR,         8, MASKED, ENABLED);

    #define SD_HOST_STANDARD_ERROR_INTERRUPT_ENABLE_ISSUE_COMMAND(__ENUM__)               \
        SD_REG_BITS_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_COMMAND_TIMEOUT_ERROR,  __ENUM__), \
        SD_REG_BITS_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_COMMAND_CRC_ERROR,      __ENUM__), \
        SD_REG_BITS_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_COMMAND_END_BIT_ERROR,  __ENUM__), \
        SD_REG_BITS_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_COMMAND_INDEX_ERROR,    __ENUM__), \
        SD_REG_BITS_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_DATA_TIMEOUT_ERROR,     __ENUM__), \
        SD_REG_BITS_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_DATA_CRC_ERROR,         __ENUM__), \
        SD_REG_BITS_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_DATA_END_BIT_ERROR,     __ENUM__), \
        SD_REG_BITS_ENUM(ERROR_INTERRUPT_STATUS_ENABLE_AUTO_CMD_ERROR,         __ENUM__)

}
