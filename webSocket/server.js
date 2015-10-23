// webSocket server

var WebSocketServer = require("ws").Server;

var wss = new WebSocketServer({port: 5555});

// bind events
wss.on("connection", function(conn)
{
    var connName = conn.upgradeReq.url.replace("/", "");

    // message event
    conn.on("message", function(message)
    {
        wss.clients.forEach(function each(client)
        {
            var chatName = client.upgradeReq.url.replace("/", "");
            if(connName !== chatName)
            {
                client.send(connName + " 说: " + message);
            }
        });
    });

    // close event
    conn.on("close", function(code, reason)
    {
        console.log("disconnected");
    });

    // error event
    conn.on("error", function(err)
    {
        console.error(err);
    });
});
