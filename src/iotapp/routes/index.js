var express = require('express');
var router = express.Router();
var buf = require('buffer');
var request = require("request");

//replace your-ip-or-domain-name with your actual ip address or domain name
//example iot.azurewebsites.com
//example yourdomainname.com
//example 47.12.67.16

// accept POST request on the homepage
router.post('/iot/myhome/livingroom/thermostat', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/livingroom/thermostat',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });




  res.send('Living room temperature recorded');
});

// accept POST request mic
router.post('/iot/myhome/livingroom/mic', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/livingroom/microphone',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('Living room sound intensity recorded');
});

// accept POST request pir
router.post('/iot/myhome/livingroom/pir', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/livingroom/pir',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('Living room pir movement recorded');
});

// accept POST request distance
router.post('/iot/myhome/livingroom/distance', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/livingroom/distance',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('Living room obstacle recorded');
});

// accept POST request gps
router.post('/iot/mydevice/location', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/mydevice/location/gps',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('device location recorded');
});

// accept POST request moisture
router.post('/iot/myhome/garden/moisture', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/garden/moisture',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('Garden moisture level recorded');
});

// accept POST request gas
router.post('/iot/myhome/kitchen/gas', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/kitchen/gas',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('Gas leak information recorded');
});

// accept POST request light
router.post('/iot/myhome/livingroom/light', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/livingroom/light',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('Light intensity recorded');
});

// accept POST request livingroom
router.post('/iot/myhome/livingroom', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/room/livingroom',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('Livingroom attributes recorded');
});

// accept POST request bedroom
router.post('/iot/myhome/bedroom', function (req, res) {
  var state = req.body;
  state.timeutc = new Date();
  state.signedby = "orangepi";
  console.log(state);

  var options = { method: 'POST',
    url: 'http://iot-idris-home.azurewebsites.net/api/iot/myhome/room/bedroom',
    headers:
     {
       'cache-control': 'no-cache',
       'content-type': 'application/json' },
    body:state,
    json: true };

  request(options, function (error, response, body) {
    if (error) throw new Error(error);

    console.log(body);
  });


  res.send('Bedroom attributes recorded');
});

// accept PUT request at /user
router.put('/user', function (req, res) {
  res.send('Got a PUT request at /user');
});

// accept DELETE request at /user
//router.delete('/user', function (req, res) {
//  res.send('Got a DELETE request at /user');
//});

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

module.exports = router;
