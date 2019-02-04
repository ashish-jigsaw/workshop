var express = require('express')
var app = express()

var fs = require('fs')

var records = []

// Load old records from local storage
fs.readFile('records.json', function(error, data) {
  if (data !== undefined) {
    records = JSON.parse(data)
    console.log(records.length + ' records loaded from local storage')
  }
})

app.get('/log/:temperature/:humidity', function (req, res) {
  console.log('req.params')
  // Create a new record
  var record = {
    temperature: req.params.temperature,
    humidity: req.params.humidity,
    light: req.params.light,
    timestamp: Date.now()
  }
  // Add to records
  records.push(record)
  // Save to local file
  fs.writeFile('records.json', JSON.stringify(records))
  // Send response
  res.send({
    status: 'ok',
    count: records.length
  })
})

app.get('/show/:count', function (req, res) {
  // Send response
  res.send(records.slice(-req.params.count))
})

app.get('/show', function (req, res) {
  // Send response
  res.send(records.slice(-3))
})

app.get('/', function (req, res) {
  res.send('Hello World!')
})

app.listen(process.env.PORT || 3000, function () {
  console.log('Example app listening on port 3000!')
})

