var spark = require('spark');
var bluebird = require('bluebird');

var deviceId = process.env.DeviceId;
var token = process.env.AccessToken;

var getDeviceName = function() {
  return new bluebird.Promise(function (resolve, reject) {
    if(!token) {
      reject("Bad Access Token");
    } else {
      spark.login({accessToken: token}).then(function (body) {
        spark.getDevice(deviceId).then(function(device) {
          resolve(device.name);    
        }, function(err){
          reject("Could not find the device");
        });
      }, function(err) {
        reject("Authentication failed");
      });
    }  
  }); 
};

var sendMessage = function(line, scrollDelay, message, callback) {
	return new bluebird.Promise(function (resolve, reject) {
    if (!token) {
      reject("Bad Access Token");  
    } else {
      spark.login({accessToken: token}).then(function(body) {
        spark.getDevice(deviceId).then(function(device) {
          device.callFunction('setActiveLin', line).then(function (data) {
            device.callFunction('setScrollDel', scrollDelay).then(function(data) {
              device.callFunction('setMessage', message).then(function(data) {
                resolve({
                  device: device.name, 
                  message: message,
                  scroll: scrollDelay,
                  line: line
                });
              }, function(err) {
                reject("setMessage");
              });
            }, function(err) {
              reject("setScrollDelay");
            });       
           }, function (err) { 
            reject("setActiveLine");                
          });  
        }, function(err) {
          reject("getDevice");
        });  
      }, function(err) {
        reject("login");
      });
    }
  });
};

module.exports.getDeviceName = getDeviceName;
module.exports.sendMessage = sendMessage;