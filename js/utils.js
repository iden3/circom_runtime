
const fnv = require("fnv-plus");

module.exports.fnvHash = fnvHash;
module.exports.flatArray = flatArray;

function flatArray(a) {
    var res = [];
    fillArray(res, a);
    return res;

    function fillArray(res, a) {
        if (Array.isArray(a)) {
            for (let i=0; i<a.length; i++) {
                fillArray(res, a[i]);
            }
        } else {
            res.push(bigInt(a));
        }
    }
}

function fnvHash(str) {
    return fnv.hash(str, 64).hex();
}
