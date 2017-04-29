/**
 ******************************************************************************
 *
 * @file       pikoblx.cpp
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2013
 * @author     dRonin, http://dronin.org Copyright (C) 2015-2017
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup Boards_dRonin dRonin board support plugin
 * @{
 * @brief Support the Piko BLX flight controller
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>
 */

#include "tinyfish.h"

#include <QIcon>

#include <uavobjectmanager.h>
#include "uavobjectutil/uavobjectutilmanager.h"
#include <extensionsystem/pluginmanager.h>
#include "board_usb_ids.h"

#include "hwtinyfish.h"

/**
 * @brief PikoBLX::PikoBLX
 *  This is the PikoBLX board definition
 */
TINYFISH::TINYFISH(void)
{
    // Common USB IDs
    addBootloaderUSBInfo(
        USBInfo(DRONIN_VID_DRONIN_BOOTLOADER, DRONIN_PID_DRONIN_BOOTLOADER, BCD_DEVICE_BOOTLOADER));
    addFirmwareUSBInfo(
        USBInfo(DRONIN_VID_DRONIN_FIRMWARE, DRONIN_PID_DRONIN_FIRMWARE, BCD_DEVICE_FIRMWARE));

    boardType = 0xB1;

    // Define the bank of channels that are connected to a given timer
    channelBanks.resize(3);
    channelBanks[0] = QVector<int> () << 1;       // TIM4
    channelBanks[1] = QVector<int> () << 2;       // TIM8
    channelBanks[2] = QVector<int> () << 3 << 4;  // TIM2
}

TINYFISH::~TINYFISH()
{
}


QString TINYFISH::shortName()
{
    return QString("tinyfish");
}

QString TINYFISH::boardDescription()
{
    return QString("tinyfish flight controller");
}

//! Return which capabilities this board has
bool TINYFISH::queryCapabilities(BoardCapabilities capability)
{
    switch (capability) {
    case BOARD_CAPABILITIES_GYROS:
    case BOARD_CAPABILITIES_ACCELS:
    case BOARD_CAPABILITIES_UPGRADEABLE:
        return true;
    case BOARD_CAPABILITIES_MAGS:
    case BOARD_CAPABILITIES_BAROS:
    default:
        break;
    }

    return false;
}

QPixmap TINYFISH::getBoardPicture()
{
    return QIcon(":/dronin/images/pikoblx.svg").pixmap(QSize(735, 718));
}

//! Determine if this board supports configuring the receiver
bool TINYFISH::isInputConfigurationSupported(Core::IBoardType::InputType type)
{
    switch (type) {
    case INPUT_TYPE_SBUS:
    case INPUT_TYPE_UNKNOWN:
        return false;
    default:
        break;
    }

    return true;
}

QString TINYFISH::getHwUAVO()
{
    return "HwTinyFISH";
}

/**
 * Configure the board to use a receiver input type on a port number
 * @param type the type of receiver to use
 * @return true if successfully configured or false otherwise
 */
bool TINYFISH::setInputType(Core::IBoardType::InputType type)
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwTinyFISH *hwTinyFISH = HwTinyFISH::GetInstance(uavoManager);
    Q_ASSERT(hwTinyFISH);
    if (!hwTinyFISH)
        return false;

    HwTinyFISH::DataFields settings = hwTinyFISH->getData();

    switch (type) {
    case INPUT_TYPE_HOTTSUMD:
        settings.Uart2 = HwTinyFISH::UART1_HOTTSUMD;
        break;
    case INPUT_TYPE_HOTTSUMH:
        settings.Uart2 = HwTinyFISH::UART1_HOTTSUMD;
        break;
    case INPUT_TYPE_SBUS:
        settings.Uart2 = HwTinyFISH::UART1_SBUS;
        break;
    case INPUT_TYPE_SBUSNONINVERTED:
        settings.Uart2 = HwTinyFISH::UART1_SBUSNONINVERTED;
        break;
    case INPUT_TYPE_IBUS:
        settings.Uart2 = HwTinyFISH::UART1_IBUS;
        break;
    case INPUT_TYPE_SRXL:
        settings.Uart2 = HwTinyFISH::UART1_SRXL;
        break;
    case INPUT_TYPE_DSM:
        settings.Uart2 = HwTinyFISH::UART1_DSM;
        break;
    case INPUT_TYPE_TBSCROSSFIRE:
        settings.Uart2 = HwTinyFISH::UART1_TBSCROSSFIRE;
        break;
    default:
        return false;
    }

    // Apply these changes
    hwTinyFISH->setData(settings);

    return true;
}

/**
 * @brief PikoBLX::getInputType fetch the currently selected input type
 * @return the selected input type
 */
Core::IBoardType::InputType TINYFISH::getInputType()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwTinyFISH *hwTinyFISH = HwTinyFISH::GetInstance(uavoManager);
    Q_ASSERT(hwTinyFISH);
    if (!hwTinyFISH)
        return INPUT_TYPE_UNKNOWN;

    HwTinyFISH::DataFields settings = hwTinyFISH->getData();

    switch (settings.Uart1) {
    case HwTinyFISH::UART1_DSM:
        return INPUT_TYPE_DSM;
    case HwTinyFISH::UART1_HOTTSUMD:
        return INPUT_TYPE_HOTTSUMD;
    case HwTinyFISH::UART1_HOTTSUMH:
        return INPUT_TYPE_HOTTSUMH;
    case HwTinyFISH::UART1_SBUS:
        return INPUT_TYPE_SBUS;
    case HwTinyFISH::UART1_SBUSNONINVERTED:
        return INPUT_TYPE_SBUSNONINVERTED;
    case HwTinyFISH::UART1_IBUS:
        return INPUT_TYPE_IBUS;
    case HwTinyFISH::UART1_SRXL:
        return INPUT_TYPE_SRXL;
    case HwTinyFISH::UART1_TBSCROSSFIRE:
        return INPUT_TYPE_TBSCROSSFIRE;
    default:
        break;
    }

    switch (settings.Uart2) {
    case HwTinyFISH::UART2_DSM:
        return INPUT_TYPE_DSM;
    case HwTinyFISH::UART2_SBUS:
        return INPUT_TYPE_SBUS;
    case HwTinyFISH::UART2_SBUSNONINVERTED:
        return INPUT_TYPE_SBUSNONINVERTED;
    case HwTinyFISH::UART2_IBUS:
        return INPUT_TYPE_IBUS;
    case HwTinyFISH::UART2_SRXL:
        return INPUT_TYPE_SRXL;
    case HwTinyFISH::UART2_HOTTSUMD:
        return INPUT_TYPE_HOTTSUMD;
    case HwTinyFISH::UART2_HOTTSUMH:
        return INPUT_TYPE_HOTTSUMH;
    case HwTinyFISH::UART2_TBSCROSSFIRE:
        return INPUT_TYPE_TBSCROSSFIRE;
    default:
        break;
    }

    switch (settings.Uart3) {
    case HwTinyFISH::UART3_DSM:
        return INPUT_TYPE_DSM;
    case HwTinyFISH::UART3_SBUS:
        return INPUT_TYPE_SBUS;
    case HwTinyFISH::UART3_SBUSNONINVERTED:
        return INPUT_TYPE_SBUSNONINVERTED;
    case HwTinyFISH::UART3_IBUS:
        return INPUT_TYPE_IBUS;
    case HwTinyFISH::UART3_SRXL:
        return INPUT_TYPE_SRXL;
    case HwTinyFISH::UART3_HOTTSUMD:
        return INPUT_TYPE_HOTTSUMD;
    case HwTinyFISH::UART3_HOTTSUMH:
        return INPUT_TYPE_HOTTSUMH;
    case HwTinyFISH::UART3_TBSCROSSFIRE:
        return INPUT_TYPE_TBSCROSSFIRE;
    default:
        break;
    }

    return INPUT_TYPE_UNKNOWN;
}

int TINYFISH::queryMaxGyroRate()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwTinyFISH *hwTinyFISH = HwTinyFISH::GetInstance(uavoManager);
    Q_ASSERT(hwTinyFISH);
    if (!hwTinyFISH)
        return 0;

    HwTinyFISH::DataFields settings = hwTinyFISH->getData();

    switch (settings.GyroRange) {
    case HwTinyFISH::GYRORANGE_250:
        return 250;
    case HwTinyFISH::GYRORANGE_500:
        return 500;
    case HwTinyFISH::GYRORANGE_1000:
        return 1000;
    case HwTinyFISH::GYRORANGE_2000:
        return 2000;
    default:
        break;
    }

    return 500;
}

QStringList TINYFISH::getAdcNames()
{
    return QStringList() << "Current"
			 << "VBAT";
}
