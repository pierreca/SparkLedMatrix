var express = require('express');
var spark = require('spark');
var router = express.Router();

router.get('/', function(req, res, next) {
  var token = req.query.token;
  if(!token) {
    res.render('deviceError', { reason: 'Authentication needed' });
  } else {
    spark.login({accessToken: token}).then(
      function (body) {
        spark.getDevice('<DEVICE_ID>').then(
          function(device) {
            res.render('index', { title: 'SparkLedMatrix', deviceName: device.name });    
          },
          function(err){
              res.render('deviceError', { reason: 'Auth error or could not find the device' });            
          });
      },
      function(err) {
        res.render('deviceError', { reason: 'Authentication failed' });
      }
    );
  }
});
  
router.post('/', function(req, res, next) {
  var token = req.query.token;
  if (!token) {
    res.render('deviceError', { reason: 'Authentication needed' });  
  } else {
    spark.login({accessToken: token}).then(
      function(body) {
        spark.getDevice('<DEVICE_ID>').then(
          function(device) {
            device.callFunction('setActiveLin', req.body.line).then(
              function (data) {
                device.callFunction('setScrollDel', req.body.scrollDelay).then(
                  function(data) {
                    device.callFunction('setMessage', req.body.message).then(
                      function(data) {
                        res.render('confirm', {
                          device: device.name, 
                          message: req.body.message,
                          scroll: req.body.scrollDelay,
                          line: req.body.line
                        });
                      },
                      function(err) {
                        res.render('deviceError', { reason: 'setMessage' });
                      }
                    );
                  },
                  function(err) {
                    res.render('deviceError', { reason: 'setScrollDelay' });
                  }
                );       
               },
              function (err) { 
                res.render('deviceError', { reason: 'setActiveLine' });                
              }
            );  
          },
          function(err) {
            res.render('deviceError', { reason: 'getDevice' });
          }
        );  
      },
      function(err) {
        res.render('deviceError', { reason: 'login' });
      }
    );
  }
});

module.exports = router;
