#
# Copyright (c) 2019 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic

import re
import collections

ConfigOption = collections.namedtuple('ConfigOption', 'range option_name help type')

PMW3360_OPTIONS = {
    'downshift_run':    ConfigOption((10,   2550),   'downshift',   'Run to Rest 1 switch time [ms]', int),
    'downshift_rest1':  ConfigOption((320,  81600),  'rest1', 'Rest 1 to Rest 2 switch time [ms]', int),
    'downshift_rest2':  ConfigOption((3200, 816000), 'rest2', 'Rest 2 to Rest 3 switch time [ms]', int),
    'cpi':              ConfigOption((100,  12000),  'cpi', 'CPI resolution', int),
}

PAW3212_OPTIONS = {
    'sleep1_timeout':  ConfigOption((32,    512),    'downshift',   'Sleep 1 switch time [ms]', int),
    'sleep2_timeout':  ConfigOption((20480, 327680), 'rest1', 'Sleep 2 switch time [ms]', int),
    'sleep3_timeout':  ConfigOption((20480, 327680), 'rest2', 'Sleep 3 switch time [ms]', int),
    'cpi':             ConfigOption((0,     2394),   'cpi', 'CPI resolution', int),
}

QOS_OPTIONS = {
    'sample_count_min':       ConfigOption((0,      65535), 'param_ble',    'Minimum number of samples needed for channel map processing', int),
    'min_channel_count':      ConfigOption((2,      37),    'param_ble',    'Minimum BLE channel count', int),
    'weight_crc_ok':          ConfigOption((-32767, 32767), 'param_ble',    'Weight of CRC OK [Fixed point with 1/100 scaling]', int),
    'weight_crc_error':       ConfigOption((-32767, 32767), 'param_ble',    'Weight of CRC ERROR [Fixed point with 1/100 scaling]', int),
    'ble_block_threshold':    ConfigOption((1,      65535), 'param_ble',    'Threshold relative to average rating for blocking BLE channels [Fixed point with 1/100 scaling]', int),
    'eval_max_count':         ConfigOption((1,      37),    'param_ble',    'Maximum number of blocked channels that can be evaluated', int),
    'eval_duration':          ConfigOption((1,      65535), 'param_ble',    'Duration of channel evaluation [seconds]', int),
    'eval_keepout_duration':  ConfigOption((1,      65535), 'param_ble',    'Duration that a channel will be blocked before considered for re-evaluation [seconds]', int),
    'eval_success_threshold': ConfigOption((1,      65535), 'param_ble',    'Threshold relative to average rating for approving blocked BLE channel under evaluation [Fixed point with 1/100 scaling]', int),
    'wifi_rating_inc':        ConfigOption((1,      65535), 'param_wifi',   'Wifi strength rating multiplier. Increase value to block wifi faster [Fixed point with 1/100 scaling]', int),
    'wifi_present_threshold': ConfigOption((1,      65535), 'param_wifi',   'Threshold relative to average rating for considering a wifi present [Fixed point with 1/100 scaling]', int),
    'wifi_active_threshold':  ConfigOption((1,      65535), 'param_wifi',   'Threshold relative to average rating for considering a wifi active(blockable) [Fixed point with 1/100 scaling]', int),
    'channel_map':            ConfigOption(('0',      '0x1FFFFFFFFF'), 'chmap', '5-byte BLE channel map bitmask', str),
    'wifi_blacklist':         ConfigOption(('0',      '1,2,...,11'), 'blacklist', 'List of blacklisted wifi channels', str),
}

BLE_BOND_OPTIONS_DONGLE = {
    'peer_erase':             ConfigOption(None, 'peer_erase',  'Trigger peer erase', None),
    'peer_search':            ConfigOption(None, 'peer_search', 'Trigger peer search', None),
}

BLE_BOND_OPTIONS_DEVICE = {
    'peer_erase':             ConfigOption(None, 'peer_erase',  'Trigger peer erase', None),
}

# Formatting details for QoS, which uses a struct containing multiple configuration values:
# OPTION_ID: (struct format, struct member names, binary to human-readable conversion function, human-readable to binary conversion function)
QOS_OPTIONS_FORMAT = {
    'blacklist' : ('<H', ['wifi_blacklist'], lambda x: str([i for i in range(0,16) if x & (1 << i) != 0])[1:-1], lambda x: sum(map(lambda y: (1 << int(y)), re.findall(r'([\d]+)', x)))),
    'chmap': ('<5s', ['channel_map'], lambda x: '0x{:02X}{:02X}{:02X}{:02X}{:02X}'.format(x[4],x[3],x[2],x[1],x[0]), None),
    'param_ble': ('<HBhhHBHHH', ['sample_count_min', 'min_channel_count', 'weight_crc_ok', 'weight_crc_error', 'ble_block_threshold', 'eval_max_count', 'eval_duration', 'eval_keepout_duration', 'eval_success_threshold'], None, None),
    'param_wifi' : ('<hhh', ['wifi_rating_inc', 'wifi_present_threshold', 'wifi_active_threshold'], None, None),
}

GMOUSE_NRF52840_CONFIG = {
    'sensor' : {
        'options' : PMW3360_OPTIONS
    },

    'ble_bond' : {
        'options' : BLE_BOND_OPTIONS_DEVICE
    }
}

DMOUSE_NRF52832_CONFIG = {
    'sensor' : {
        'options' : PAW3212_OPTIONS
    },

    'ble_bond' : {
        'options' : BLE_BOND_OPTIONS_DEVICE
    }
}

DMOUSE_NRF52810_CONFIG = {
    'sensor' : {
        'options' : PAW3212_OPTIONS
    },

    'ble_bond' : {
        'options' : BLE_BOND_OPTIONS_DEVICE
    }
}

KBD_NRF52832_CONFIG = {
    'ble_bond' : {
        'options' : BLE_BOND_OPTIONS_DEVICE
    }
}

DONGLE_NRF52840_CONFIG = {
    'qos' : {
        'options' : QOS_OPTIONS,
        'format' : QOS_OPTIONS_FORMAT
    },

    'ble_bond' : {
        'options' : BLE_BOND_OPTIONS_DONGLE
    }
}

DEVICE = {
    'desktop_mouse_nrf52832' : {
        'vid' : 0x1915,
        'pid' : 0x52DA,
        'config' : DMOUSE_NRF52832_CONFIG,
        'stream_led_cnt' : 0,
    },
    'desktop_mouse_nrf52810' : {
        'vid' : 0x1915,
        'pid' : 0x52DB,
        'config' : DMOUSE_NRF52810_CONFIG,
        'stream_led_cnt' : 0,
    },
    'gaming_mouse' : {
        'vid' : 0x1915,
        'pid' : 0x52DE,
        'config' : GMOUSE_NRF52840_CONFIG,
        'stream_led_cnt' : 2,
    },
    'keyboard' : {
        'vid' : 0x1915,
        'pid' : 0x52DD,
        'config' : KBD_NRF52832_CONFIG,
        'stream_led_cnt' : 0,
    },
    'dongle' : {
        'vid' : 0x1915,
        'pid' : 0x52DC,
        'config' : DONGLE_NRF52840_CONFIG,
        'stream_led_cnt' : 0,
    }
}


def get_device_pid(device_type):
    return DEVICE[device_type]['pid']


def get_device_vid(device_type):
    return DEVICE[device_type]['vid']


def get_device_type(pid):
    for device_type in DEVICE:
        if DEVICE[device_type]['pid'] == pid:
            return device_type
    return None
