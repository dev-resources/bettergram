/*
This file is part of Bettergram.

For license and copyright information please follow this link:
https://github.com/bettergram/bettergram/blob/master/LEGAL
*/
#pragma once

#define TDESKTOP_REQUESTED_ALPHA_VERSION (0ULL)

#ifdef TDESKTOP_OFFICIAL_TARGET
#define TDESKTOP_ALPHA_VERSION TDESKTOP_REQUESTED_ALPHA_VERSION
#else // TDESKTOP_OFFICIAL_TARGET
#define TDESKTOP_ALPHA_VERSION (0ULL)
#endif // TDESKTOP_OFFICIAL_TARGET

constexpr auto AppVersion = 1006002;
constexpr auto AppVersionStr = "1.6.2";
constexpr auto AppBetaVersion = false;
constexpr auto AppAlphaVersion = TDESKTOP_ALPHA_VERSION;
