#include "document.h"

const char* htm = u8"_(<!doctype html>
<html lang=en>
<head>
<meta name=viewport content='width=device-width, initial-scale=1' charset=UTF-8>
<title>tomo shock collar</title>
<link href=https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css rel=stylesheet integrity=sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD crossorigin=anonymous>
<link rel=stylesheet media=screen href=https://fontlibrary.org//face/segment7 type=text/css />
</head>
<body id=main_body data-bs-theme=dark>
<main>
<center>
<font size=7>🦊</font><br>
<div style=width:80%;max-width:10cm;min-width:4cm>
<select name=action class="form-select form-select-lg mb-3" id=action onchange=return_to_last_value()>
<option value=0>Shock</option>
<option value=1 selected=selected>Vibrate</option>
<option value=2>Sound</option>
</select>
<br>
<input type=range min=1 max=100 value=50 class=form-range id=myRange>
<br>
<span id=demo style="text-align:left;font-family:'Segment7Standard';font-size:42px"></span>
<br>
<button type=button class="btn btn-danger" onclick=submit() value=OK>SEND</button>
</div>
</center>
</main>
<footer style=position:fixed;bottom:0;left:0;right:0>
<div>
<button class="btn btn-primary" type=button data-bs-toggle=collapse data-bs-target=#options aria-expanded=false>
⚙️
</button>
</div>
<div id=options class=collapse style=padding:20px;background:var(--bs-tertiary-bg)>
<div>
<input type=radio name=color_theme id=dark_theme value=dark onchange=sel_theme() checked=checked>
<label for=dark_theme>Dark theme</label>
</div>
<div>
<input type=radio name=color_theme id=light_theme value=light onchange=sel_theme()>
<label for=light_theme>Light theme</label>
</div>
</div>
</footer>
<script>const mainbody=document.getElementById("main_body");const option=document.getElementById("action");const slider=document.getElementById("myRange");const output=document.getElementById("demo");const options=document.getElementById("options");output.innerHTML=slider.value;function setCookie(c,d,e){var a="";if(e){var b=new Date();b.setTime(b.getTime()+(e*24*60*60*1000));a="; expires="+b.toUTCString()}document.cookie=c+"="+(d||"")+a+"; path=/"}function getCookie(b){var e=b+"=";var a=document.cookie.split(";");for(var d=0;d<a.length;d++){var f=a[d];while(f.charAt(0)==" "){f=f.substring(1,f.length)}if(f.indexOf(e)==0){return f.substring(e.length,f.length)}}return null}function eraseCookie(a){document.cookie=a+"=; Path=/; Expires=Thu, 01 Jan 1970 00:00:01 GMT;"}var shock_value=1;var vibrate_value=1;var sound_value=1;if(!(getCookie("shock_value")||getCookie("vibrate_value")||getCookie("sound_value"))){setCookie("shock_value",shock_value,3);setCookie("vibrate_value",vibrate_value,3);setCookie("sound_value",sound_value,3)}else{shock_value=getCookie("shock_value");vibrate_value=getCookie("vibrate_value");sound_value=getCookie("sound_value")}return_to_last_value();slider.oninput=function(){if(option.value==0){shock_value=this.value;setCookie("shock_value",shock_value,3)}if(option.value==1){vibrate_value=this.value;setCookie("vibrate_value",vibrate_value,3)}if(option.value==2){sound_value=this.value;setCookie("sound_value",sound_value,3)}output.innerHTML=this.value};function submit(){fetch("/",{method:"POST",headers:{Accept:"application/x-www-form-urlencoded","Content-Type":"application/x-www-form-urlencoded"},body:"i="+slider.value+"&type="+action.value})}function return_to_last_value(){if(option.value==0){set_slider_value(shock_value);return}if(option.value==1){set_slider_value(vibrate_value);return}if(option.value==2){set_slider_value(sound_value);return}}function set_slider_value(a){slider.value=a;output.innerHTML=a}function sel_theme(){if(document.getElementById("dark_theme").checked==true){mainbody.setAttribute("data-bs-theme","dark")}if(document.getElementById("light_theme").checked==true){mainbody.setAttribute("data-bs-theme","light")}};</script>
<script src=https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js integrity=sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN crossorigin=anonymous></script>
</body>
</html>)_";