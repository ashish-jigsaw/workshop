var express = require('express')
var app = express()

var fs = require('fs')

var records = []

app.get('/log/:temperature/:humidity', function (req, res) {
  console.log(req.params)
  // Create a new record
  var record = {
    temperature: req.params.temperature,
    humidity: req.params.humidity,
    light: req.params.light,
    timestamp: Date.now()
  }
  // Add to records
  records.push(record)
  // Send response
  res.send({
    status: 'ok',
    count: records.length
  })
})

app.get('/', function (req, res) {
  res.send('Hello World!')
})

app.listen(process.env.PORT || 3000, function () {
  console.log('Example app listening on port 3000!')
})

