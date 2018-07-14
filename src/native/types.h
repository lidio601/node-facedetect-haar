//
// Created by Fabio Cigliano on 02/07/18.
//

#ifndef CAMERA_WRAPPER_TYPES_H
#define CAMERA_WRAPPER_TYPES_H

// Core
#include <iostream>
#include <fstream>
#include <stdio.h>

// Node.js deps
#include <node.h>
#include <v8.h>

// OpenCV deps
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>

// OpenCV face deps
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>

#include <uv.h>
#include <vector>

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

using namespace v8;

//Define functions in scope
std::string stringValue(Local<Value> value);

/*
 * Thread message
 */
struct TMessage {
    // camera frame size
    int32_t width, height;

    bool resize;

    // frame encoding
    std::string codec;

    // facedetect enabled
    bool faceDetect;

    // frame callback function
    Persistent<Function> callback;

    // OpenCV Camera capture
    cv::VideoCapture *capture;

    bool started;

    /*
     * Face detect
     */
    cv::DetectionBasedTracker *detector;

    ~TMessage() {
        callback.Reset();
        delete capture;
        delete detector;
    }
};

/**
 * Message sent to Node.js
 */
struct AsyncMessage {
    std::vector<unsigned char> image;
    cv::Mat frame;
    bool window;
    bool faceDetected;

    ~AsyncMessage() {
        image.clear();
        frame.release();
    }
};

extern uv_async_t async;
extern TMessage *bag;

#endif //CAMERA_WRAPPER_TYPES_H