#include "ofxTrackingCamera.h"

ofxTrackingCamera::ofxTrackingCamera(){
    dampen             = 0.4;

    targetPosition     = ofVec3f(0.0, 0.0, 0.0);
    cameraBasePosition = ofVec3f(0.0, 0.0, -1.0);
    dirVec             = ofVec3f(1.0, 1.0, 1.0);
}

ofxTrackingCamera::~ofxTrackingCamera(){

}

void ofxTrackingCamera::updateCameraSettings(ofVec3f target, float distance = 10.0){
    targetPosition = target;
    cameraPosition = targetPosition;
    
    float rotationAngle;
    ofVec3f rotationAxis;
     
    rotation.getRotate(rotationAngle, rotationAxis);
     
    cameraPosition.rotate(rotationAngle, rotationAxis);
    targetPosition.rotate(rotationAngle, rotationAxis);
     
    // add rotation to upvec
    ofVec3f upVec = ofVec3f(0.0, 1.0, 0.0);
    upVec.rotate(rotationAngle, rotationAxis);
    
    // add vector to move camera
    ofVec3f vecFromTarget = dirVec.getScaled(distance);
    cameraPosition += vecFromTarget;
    
    this->setPosition(cameraPosition);
    this->lookAt(targetPosition, upVec);
}

void ofxTrackingCamera::setMouseRotation(ofVec2f mousePosition){
    ofQuaternion yRot((mousePosition.x - lastMousePosition.x)*dampen, yAxis);
    ofQuaternion xRot((mousePosition.y - lastMousePosition.y)*dampen, xAxis);
    
    rotation *= yRot*xRot;
    lastMousePosition = mousePosition;
}

void ofxTrackingCamera::updateLastMousePosition(ofVec2f mousePosition){
    lastMousePosition = mousePosition;
}

void ofxTrackingCamera::calcCameraAxis(){
    zAxis = cameraPosition - targetPosition;
    zAxis.normalize();
    xAxis = ofVec3f(0.0, 1.0, 0.0).getCrossed(zAxis);
    xAxis.normalize();
    yAxis = zAxis.getCrossed(xAxis);
    yAxis.normalize();
}

void ofxTrackingCamera::pushRotateMatrix(){
    float rotateAngle;
    ofVec3f rotateAxis;
    
    rotation.getRotate(rotateAngle, rotateAxis);
    ofRotate(rotateAngle, rotateAxis.x, rotateAxis.y, rotateAxis.z);
    ofPushMatrix();
}

void ofxTrackingCamera::popRotateMatrix(){
    ofPopMatrix();
}
