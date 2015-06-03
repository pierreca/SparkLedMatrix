var express = require('express');
var router = express.Router();
var sparkLedMatrix = require('./sparkledmatrix');

router.get('/', function(req, res, next) {
  sparkLedMatrix.getDeviceName().then(function (deviceName) {
    res.render('index', { title: 'SparkLedMatrix', deviceName: deviceName });
  }).catch(function (error) {    
    res.render('deviceError', { reason: error });
  });
});
  
router.post('/', function(req, res, next) {
  sparkLedMatrix.sendMessage(req.body.line, req.body.scrollDelay, req.body.message).then(function (confirmation) {
    res.render('confirm', confirmation);
  }).catch(function(error) {
    res.render('deviceError', {reason: error});
  });
});

router.post('/api', function (req, res, next) {
  res.sendStatus(200);
});

module.exports = router;
