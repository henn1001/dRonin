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

#include "kkng.h"

#include <QIcon>

#include <uavobjectmanager.h>
#include "uavobjectutil/uavobjectutilmanager.h"
#include <extensionsystem/pluginmanager.h>
#include "board_usb_ids.h"

#include "hwkkng.h"

/**
 * @brief PikoBLX::PikoBLX
 *  This is the PikoBLX board definition
 */
KKNG::KKNG(void)
{
    // Common USB IDs
    addBootloaderUSBInfo(
        USBInfo(DRONIN_VID_DRONIN_BOOTLOADER, DRONIN_PID_DRONIN_BOOTLOADER, BCD_DEVICE_BOOTLOADER));
    addFirmwareUSBInfo(
        USBInfo(DRONIN_VID_DRONIN_FIRMWARE, DRONIN_PID_DRONIN_FIRMWARE, BCD_DEVICE_FIRMWARE));

    boardType = 0xB0;

    // Define the bank of channels that are connected to a given timer
    channelBanks.resize(3);
    channelBanks[0] = QVector<int> () << 1 << 2;       // TIM4
    channelBanks[1] = QVector<int> () << 3;            // TIM17
    channelBanks[2] = QVector<int> () << 4;            // TIM16
}

KKNG::~KKNG()
{
}


QString KKNG::shortName()
{
    return QString("kkng");
}

QString KKNG::boardDescription()
{
    return QString("kkng flight controller");
}

//! Return which capabilities this board has
bool KKNG::queryCapabilities(BoardCapabilities capability)
{
    switch (capability) {
    case BOARD_CAPABILITIES_GYROS:
    case BOARD_CAPABILITIES_ACCELS:
    case BOARD_CAPABILITIES_MAGS:
    case BOARD_CAPABILITIES_BAROS:
    case BOARD_CAPABILITIES_UPGRADEABLE:
        return true;
    default:
        break;
    }

    return false;
}

QPixmap KKNG::getBoardPicture()
{
    return QIcon(":/dronin/images/pikoblx.svg").pixmap(QSize(735, 718));
}

//! Determine if this board supports configuring the receiver
bool KKNG::isInputConfigurationSupported(Core::IBoardType::InputType type)
{
    switch (type) {
    case INPUT_TYPE_PWM:
    case INPUT_TYPE_UNKNOWN:
        return false;
    default:
        break;
    }

    return true;
}

QString KKNG::getHwUAVO()
{
    return "HwKkng";
}

/**
 * Configure the board to use a receiver input type on a port number
 * @param type the type of receiver to use
 * @return true if successfully configured or false otherwise
 */
bool KKNG::setInputType(Core::IBoardType::InputType type)
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwKkng *hwKkng = HwKkng::GetInstance(uavoManager);
    Q_ASSERT(hwKkng);
    if (!hwKkng)
        return false;

    HwKkng::DataFields settings = hwKkng->getData();

    switch (type) {
    case INPUT_TYPE_PPM:
        settings.RcvrPort = HwKkng::RCVRPORT_PPM;
        break;
    default:
        return false;
    }

    // Apply these changes
    hwKkng->setData(settings);

    return true;
}

/**
 * @brief PikoBLX::getInputType fetch the currently selected input type
 * @return the selected input type
 */
Core::IBoardType::InputType KKNG::getInputType()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwKkng *hwKkng = HwKkng::GetInstance(uavoManager);
    Q_ASSERT(hwKkng);
    if (!hwKkng)
        return INPUT_TYPE_UNKNOWN;

    HwKkng::DataFields settings = hwKkng->getData();

    switch(settings.RcvrPort) {
    case HwKkng::RCVRPORT_PPM:
        return INPUT_TYPE_PPM;
    default:
        return INPUT_TYPE_UNKNOWN;
    }
}

int KKNG::queryMaxGyroRate()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwKkng *hwKkng = HwKkng::GetInstance(uavoManager);
    Q_ASSERT(hwKkng);
    if (!hwKkng)
        return 0;

    HwKkng::DataFields settings = hwKkng->getData();

    switch (settings.GyroRange) {
    case HwKkng::GYRORANGE_250:
        return 250;
    case HwKkng::GYRORANGE_500:
        return 500;
    case HwKkng::GYRORANGE_1000:
        return 1000;
    case HwKkng::GYRORANGE_2000:
        return 2000;
    default:
        break;
    }

    return 500;
}

QStringList KKNG::getAdcNames()
{
    return QStringList() << "VBAT" 
			 << "RSSI" 
			 << "Current";
}
