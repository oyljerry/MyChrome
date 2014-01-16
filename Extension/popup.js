var port;

function init(){    
    
    $('#msgconnect').click(function() {
		console.log('connect');
		port = chrome.runtime.connectNative('com.myext.mymsg');
		port.onMessage.addListener(function(msg) {
		  console.log("Received" + JSON.stringify(msg));
		});
		port.onDisconnect.addListener(function() {
		  console.log("Disconnected");
		});
        return true;
    });
	
	$('#msgsend').click(function() {
		port.postMessage({ text:"Hello", name:"ChromeExt" });
		console.log("Post");
        return true;
    });

    $('#getcookies').click(function() {
        console.log('get cookies');
        try{
            chrome.cookies.getAll({},function (cookie){
                console.log(cookie.length);

                /*for(i=0;i<cookie.length;i++){
                    console.log(JSON.stringify(cookie[i]));

                }*/
            });
        }
        catch(err){
            console.log(err);

        }

        /*chrome.cookies.getAllCookieStores(function (cookiestores){
        for(i=0; i<cookiestores.length; i++){
            console.log(JSON.stringify(cookiestores[i]));
        }});*/
    });
    
}

$(document).ready(function(){
    init();

});