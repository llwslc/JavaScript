var dsp = require("./build/Release/testAddons.node")


console.log(dsp.hello());
console.log("-----------------");
console.log(dsp.add(1, 1));
console.log("=================");
console.log(dsp.runcb(1, function(res){console.log("res:", res)}));
console.log("-----------------");
console.log(dsp.testType(1, 1.1, false, "~", [1,2,3], {hello: "world"}, undefined));
console.log("=================");
console.log(dsp.returnStr());
console.log("-----------------");
console.log(dsp.returnNum());
console.log("=================");
console.log(dsp.returnArr());
console.log("-----------------");
console.log(dsp.returnObj());
console.log("=================");
console.log(dsp.runThread());
console.log("-----------------");
console.log(dsp.returnGlobal());
console.log("=================");
