var express = require("express");
var path = require('path')
var app = express();

app.get('/', function (req, res)
{
    app.use(express.static("client"));
    res.sendFile(__dirname + "/client/index.html");
});

app.listen(3000, function ()
{
    console.log("Web server has started.\nPlease log on http://127.0.0.1:3000/index.html");
});