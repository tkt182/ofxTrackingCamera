#ifndef __ofxTrackingCamera__
#define __ofxTrackingCamera__


#include "ofMain.h"

class ofxTrackingCamera : public ofCamera {
    
public:

    ofxTrackingCamera();
    ~ofxTrackingCamera();

    void updateCameraSettings(ofVec3f targetPosition, float distance);
    void setMouseRotation(ofVec2f mouse);
    void updateLastMousePosition(ofVec2f mouse);
    void calcCameraAxis();
    void pushRotateMatrix();
    void popRotateMatrix();
    
private:

    ofQuaternion rotation;
    
    ofVec3f dirVec;              // direction from camera to target
    ofVec3f targetPosition;      // camera target
    ofVec3f cameraBasePosition;  // base camera position
    ofVec3f cameraPosition;      // calculated camera position
    
    ofVec3f xAxis;
    ofVec3f yAxis;
    ofVec3f zAxis;
    
    
    ofVec2f lastMousePosition;   // last mouse click postion
    float dampen;                // dampen of mouse rotation

};


#endif
