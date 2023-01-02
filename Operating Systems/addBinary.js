let arr = ['stanley', 'vic', 'popo', 'pipi'];
let res = ''

arr.sort(function(a, b) {
  return a.length - b.length;
});

arr = arr.reverse();

for(let i = 0; i < arr.length; i++)
    res += arr[i] + ' ';

console.log(res);