var express = require("express");
var path = require('path')
var app = express();

app.get('/', function (req, res)
{
    app.use(express.static("html"));
    res.sendFile(__dirname + "/html/index.html");
});

app.post('/pic', function(erq, res)
{});

app.listen(3000, function ()
{
    console.log("Web server has started.\nPlease log on http://127.0.0.1:3000/index.html");
});