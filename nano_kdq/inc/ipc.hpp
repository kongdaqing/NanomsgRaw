#ifndef IPC_HPP
#define IPC_HPP

#define  CHASSIS_LINK_PUB ("tcp://*:7368")
#define  CHASSIS_LINK_SUB ("tcp://127.0.0.1:7368")
#define  CHASSIS_LINK_IPC_DOWNSTREAM_SUB ("ipc:///tmp/chassislinksub.ipc")

#define STEREO_CAMERA_JPEG_PUB  ("tcp://*:7367")

#define VXO_POSE_PUB            ("tcp://*:7369")
#define VXO_POSE_SUB            ("tcp://127.0.0.1:7369")

#define STEREO_CAMERA_PUB ("tcp://*:7370")
#define STEREO_CAMERA_SUB ("tcp://127.0.0.1:7370")
#define VINS_POSE_IPC           ("ipc:///tmp/vinspose.ipc")
#define VINS_POINTCLOUD_IPC  ("ipc:///tmp/vinspointcloud.ipc")

#define VINS_POSE_PUB           ("tcp://*:7371")
#define VINS_POSE_SUB           ("tcp://127.0.0.1:7371")

#endif // IPC_HPP
