var express = require('express');
var router = express.Router();
var sparkLedMatrix = require('./sparkledmatrix');

router.get('/', function (req, res, next) {
  sparkLedMatrix.getDeviceName().then(function (deviceName) {
    res.render('index', { title: 'SparkLedMatrix', deviceName: deviceName });
  }).catch(function (error) {    
    res.render('deviceError', { reason: error });
  });
});
  
router.post('/', function (req, res, next) {
  sparkLedMatrix.sendMessage(req.body.line, req.body.scrollDelay, req.body.message).then(function (confirmation) {
    res.render('confirm', confirmation);
  }).catch(function(error) {
    res.render('deviceError', {reason: error});
  });
});

router.post('/api', function (req, res, next) {
  if(req.body.line && req.body.scrollDelay && req.body.message) {
    sparkLedMatrix.sendMessage(req.body.line, req.body.scrollDelay, req.body.message).then(function (confirmation) {
      res.status = 200;
      res.send(req.body);
    }).catch(function(error) {
      res.status = 400;
      res.send(error);
    });
  } else {
    res.status = 400;
    res.send ('Request does not contain all required fields');
  }
  
});

module.exports = router;
