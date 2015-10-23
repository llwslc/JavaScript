//websocket client
var wsClient = {};

wsClient.wsInit = function(name)
{
    var ws = new WebSocket("ws://localhost:5555/" + name);

    ws.onopen = function()
    {
        console.log("Opened");
    };

    ws.onmessage = function(evt)
    {
        wsRecv(evt.data);
    };

    ws.onclose = function()
    {
        console.log("Closed");
    };

    ws.onerror = function(err)
    {
        console.log("Error: " + err);
    };

    this.ws = ws;
}

wsClient.wsClose = function()
{
    this.ws.close();
}

wsClient.sendMsg = function(msgStr)
{
    this.ws.send(msgStr);
}
