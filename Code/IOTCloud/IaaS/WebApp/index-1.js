var express = require('express')
var app = express()

app.get('/log/:temperature/:humidity', function (req, res) {
  console.log(req.params)
  res.send({
	  status: 'ok',
	  })
})  

app.get('/', function (req, res) {
  res.send('Hello World!')
})

app.listen(process.env.PORT || 3000, function () {
  console.log('Example app listening on port 3000!')
})