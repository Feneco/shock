#include "document.h"

const char* Document::html = "<!doctype html>\n\
<html lang=en>\n\
<head>\n\
<meta name=viewport content='width=device-width, initial-scale=1' charset=UTF-8>\n\
<title>tomo shock collar</title>\n\
<link href=https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css rel=stylesheet integrity=sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD crossorigin=anonymous>\n\
<link rel=stylesheet media=screen href=https://fontlibrary.org//face/segment7 type=text/css />\n\
</head>\n\
<body id=main_body data-bs-theme=dark>\n\
<main>\n\
<div class=container-md style=text-align:center;max-width:14cm>\n\
<div class=display-1>🦊</div>\n\
<div>\n\
<div class=\"form-check form-switch\" style=text-align:left>\n\
<input class=form-check-input type=checkbox role=switch id=safemode onchange=safemodechange() checked>\n\
<label class=form-check-label for=safemode>Safe mode</label>\n\
</div>\n\
<select name=action class=\"form-select form-select-lg mb-3\" id=action onchange=return_to_last_value()>\n\
<option value=0>Shock</option>\n\
<option value=1 selected=selected>Vibrate</option>\n\
<option value=2>Sound</option>\n\
</select>\n\
<br>\n\
<input type=range min=1 max=100 value=50 class=form-range id=myRange>\n\
<br>\n\
<div id=demo style=\"text-align:center;font-family:'Segment7Standard';font-size:42px\"></div>\n\
<br>\n\
<button type=button class=\"btn btn-danger\" onclick=submit() value=OK id=sendbutton disabled>SEND</button>\n\
</div>\n\
</div>\n\
</main>\n\
<footer style=position:fixed;bottom:0;left:0;right:0>\n\
<div>\n\
<button class=\"btn btn-secondary\" type=button data-bs-toggle=collapse data-bs-target=#options aria-expanded=false>\n\
⚙️\n\
</button>\n\
</div>\n\
<div id=options class=collapse style=padding:20px;background:var(--bs-tertiary-bg)>\n\
<div>\n\
<input type=radio name=color_theme id=dark_theme value=dark onchange=sel_theme() checked=checked>\n\
<label for=dark_theme>Dark theme</label>\n\
</div>\n\
<div>\n\
<input type=radio name=color_theme id=light_theme value=light onchange=sel_theme()>\n\
<label for=light_theme>Light theme</label>\n\
</div>\n\
</div>\n\
</footer>\n\
<script>const mainbody=document.getElementById(\"main_body\");const option=document.getElementById(\"action\");const slider=document.getElementById(\"myRange\");const output=document.getElementById(\"demo\");const options=document.getElementById(\"options\");const safeswitch=document.getElementById(\"safemode\");const sendbutton=document.getElementById(\"sendbutton\");output.innerHTML=slider.value;function setCookie(c,d,e){var a=\"\";if(e){var b=new Date();b.setTime(b.getTime()+(e*24*60*60*1000));a=\"; expires=\"+b.toUTCString()}document.cookie=c+\"=\"+(d||\"\")+a+\"; path=/\"}function getCookie(b){var e=b+\"=\";var a=document.cookie.split(\";\");for(var d=0;d<a.length;d++){var f=a[d];while(f.charAt(0)==\" \"){f=f.substring(1,f.length)}if(f.indexOf(e)==0){return f.substring(e.length,f.length)}}return null}function eraseCookie(a){document.cookie=a+\"=; Path=/; Expires=Thu, 01 Jan 1970 00:00:01 GMT;\"}var shock_value=1;var vibrate_value=1;var sound_value=1;if(getCookie(\"shock_value\")===null||getCookie(\"vibrate_value\")===null||getCookie(\"sound_value\")===null){setCookie(\"shock_value\",shock_value,3);setCookie(\"vibrate_value\",vibrate_value,3);setCookie(\"sound_value\",sound_value,3)}else{shock_value=getCookie(\"shock_value\");vibrate_value=getCookie(\"vibrate_value\");sound_value=getCookie(\"sound_value\")}safeswitch.checked=true;return_to_last_value();sel_theme();function safemodechange(){sendbutton.disabled=safeswitch.checked}slider.oninput=function(){if(option.value==0){shock_value=this.value;setCookie(\"shock_value\",shock_value,3)}if(option.value==1){vibrate_value=this.value;setCookie(\"vibrate_value\",vibrate_value,3)}if(option.value==2){sound_value=this.value;setCookie(\"sound_value\",sound_value,3)}output.innerHTML=this.value};function submit(){fetch(\"/\",{method:\"POST\",headers:{Accept:\"application/x-www-form-urlencoded\",\"Content-Type\":\"application/x-www-form-urlencoded\"},body:\"i=\"+slider.value+\"&type=\"+action.value})}function return_to_last_value(){if(option.value==0){set_slider_value(shock_value);return}if(option.value==1){set_slider_value(vibrate_value);return}if(option.value==2){set_slider_value(sound_value);return}}function set_slider_value(a){slider.value=a;output.innerHTML=a}function sel_theme(){if(document.getElementById(\"dark_theme\").checked==true){mainbody.setAttribute(\"data-bs-theme\",\"dark\")}if(document.getElementById(\"light_theme\").checked==true){mainbody.setAttribute(\"data-bs-theme\",\"light\")}};</script>\n\
<script src=https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js integrity=sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN crossorigin=anonymous></script>\n\
</body>\n\
</html>";