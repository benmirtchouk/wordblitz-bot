b = $(".board");
ch = b.children

S = ''
for(var i=1;i<=16;i++){
    L = b.children[i].children[1].innerText;
    S += L;
}

console.log(S);