javascript:
(function(){
function setCookie(cname,cvalue,exdays,path){
    var d=new Date();
    d.setTime(d.getTime()+(exdays*24*60*60*1000));
    var expires="expires="+d.toUTCString();
    document.cookie=cname+"="+cvalue+"; "+expires+"; path="+path;
}
function getCookie(cname){
    var name=cname+"=";
    var ca=document.cookie.split(';');
    for(var i=0; i<ca.length; i++){
        var c=ca[i];
        while(c.charAt(0)==' ')c=c.substring(1);
        if(c.indexOf(name)!=-1)return c.substring(name.length,c.length);
    }
    return "";
}
var temp=getCookie("id");
setCookie("id",getCookie("temp_id"),365,"/oj");
setCookie("temp_id",temp,365,"/oj");
location.reload();
})();
