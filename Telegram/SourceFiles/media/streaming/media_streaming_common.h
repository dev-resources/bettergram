/*
This file is part of Bettergram.

For license and copyright information please follow this link:
https://github.com/bettergram/bettergram/blob/master/LEGAL
*/
#pragma once

namespace Media {

constexpr auto kTimeUnknown = std::numeric_limits<crl::time>::min();
constexpr auto kDurationMax = crl::time(std::numeric_limits<int>::max());
constexpr auto kDurationUnavailable = std::numeric_limits<crl::time>::max();

namespace Audio {
bool SupportsSpeedControl();
} // namespace Audio

namespace Streaming {

inline bool SupportsSpeedControl() {
	return Media::Audio::SupportsSpeedControl();
}

class VideoTrack;
class AudioTrack;

enum class Mode {
	Both,
	Audio,
	Video,
	Inspection,
};

struct PlaybackOptions {
	Mode mode = Mode::Both;
	crl::time position = 0;
	float64 speed = 1.; // Valid values between 0.5 and 2.
	AudioMsgId audioId;
	bool syncVideoByAudio = true;
	bool dropStaleFrames = true;
	bool loop = false;
};

struct TrackState {
	crl::time position = kTimeUnknown;
	crl::time receivedTill = kTimeUnknown;
	crl::time duration = kTimeUnknown;
};

struct VideoInformation {
	TrackState state;
	QSize size;
	QImage cover;
	int rotation = 0;
};

struct AudioInformation {
	TrackState state;
};

struct Information {
	VideoInformation video;
	AudioInformation audio;
};

template <typename Track>
struct PreloadedUpdate {
	crl::time till = kTimeUnknown;
};

template <typename Track>
struct PlaybackUpdate {
	crl::time position = kTimeUnknown;
};

using PreloadedVideo = PreloadedUpdate<VideoTrack>;
using UpdateVideo = PlaybackUpdate<VideoTrack>;
using PreloadedAudio = PreloadedUpdate<AudioTrack>;
using UpdateAudio = PlaybackUpdate<AudioTrack>;

struct WaitingForData {
	bool waiting = false;
};

struct MutedByOther {
};

struct Finished {
};

struct Update {
	base::variant<
		Information,
		PreloadedVideo,
		UpdateVideo,
		PreloadedAudio,
		UpdateAudio,
		WaitingForData,
		MutedByOther,
		Finished> data;
};

enum class Error {
	OpenFailed,
	LoadFailed,
	InvalidData,
	NotStreamable,
};

struct FrameRequest {
	QSize resize;
	QSize outer;
	ImageRoundRadius radius = ImageRoundRadius();
	RectParts corners = RectPart::AllCorners;

	bool empty() const {
		return resize.isEmpty();
	}

	bool operator==(const FrameRequest &other) const {
		return (resize == other.resize)
			&& (outer == other.outer)
			&& (radius == other.radius)
			&& (corners == other.corners);
	}
	bool operator!=(const FrameRequest &other) const {
		return !(*this == other);
	}
};

} // namespace Streaming
} // namespace Media