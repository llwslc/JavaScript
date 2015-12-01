var dsp = require("./build/Release/testAddons.node")




console.log(dsp.hello());
console.log("-----------------");
console.log(dsp.add(1, 1));
console.log("=================");
console.log(dsp.runcb(1, function(res){console.log("res:", res)}));
console.log("-----------------");
console.log(dsp.testType(1, "~", [1,2,3], {hello: "world"}));
