; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/cwd.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@cwd = global i8* null, align 8
@.str = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"..\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"/\00", align 1

; Function Attrs: nounwind uwtable
define i32 @bftpd_cwd_chdir(i8* %dir) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %dir.addr = alloca i8*, align 8
  %tmp = alloca i8*, align 8
  store i8* %dir, i8** %dir.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dir.addr, metadata !29, metadata !30), !dbg !31
  call void @llvm.dbg.declare(metadata i8** %tmp, metadata !32, metadata !30), !dbg !33
  %0 = load i8*, i8** %dir.addr, align 8, !dbg !34
  %call = call i8* @bftpd_cwd_mappath(i8* %0), !dbg !35
  store i8* %call, i8** %tmp, align 8, !dbg !33
  %1 = load i8*, i8** %tmp, align 8, !dbg !36
  %call1 = call i32 @chdir(i8* %1) #6, !dbg !38
  %tobool = icmp ne i32 %call1, 0, !dbg !38
  br i1 %tobool, label %if.then, label %if.end, !dbg !39

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %tmp, align 8, !dbg !40
  call void @free(i8* %2) #6, !dbg !42
  %call2 = call i32* @__errno_location() #1, !dbg !43
  %3 = load i32, i32* %call2, align 4, !dbg !43
  store i32 %3, i32* %retval, align 4, !dbg !44
  br label %return, !dbg !44

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** @cwd, align 8, !dbg !45
  %5 = load i8*, i8** %tmp, align 8, !dbg !46
  %call3 = call i64 @strlen(i8* %5) #7, !dbg !47
  %add = add i64 %call3, 1, !dbg !48
  %call4 = call i8* @realloc(i8* %4, i64 %add) #6, !dbg !49
  store i8* %call4, i8** @cwd, align 8, !dbg !51
  %6 = load i8*, i8** @cwd, align 8, !dbg !52
  %7 = load i8*, i8** %tmp, align 8, !dbg !53
  %call5 = call i8* @strcpy(i8* %6, i8* %7) #6, !dbg !54
  call void (...) @new_umask(), !dbg !55
  %8 = load i8*, i8** %tmp, align 8, !dbg !56
  call void @free(i8* %8) #6, !dbg !57
  store i32 0, i32* %retval, align 4, !dbg !58
  br label %return, !dbg !58

return:                                           ; preds = %if.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !59
  ret i32 %9, !dbg !59
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i8* @bftpd_cwd_mappath(i8* %path) #0 !dbg !17 {
entry:
  %retval = alloca i8*, align 8
  %path.addr = alloca i8*, align 8
  %result = alloca i8*, align 8
  %path2 = alloca i8*, align 8
  %tmp = alloca i8*, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !60, metadata !30), !dbg !61
  call void @llvm.dbg.declare(metadata i8** %result, metadata !62, metadata !30), !dbg !63
  %0 = load i8*, i8** %path.addr, align 8, !dbg !64
  %call = call i64 @strlen(i8* %0) #7, !dbg !65
  %1 = load i8*, i8** @cwd, align 8, !dbg !66
  %call1 = call i64 @strlen(i8* %1) #7, !dbg !67
  %add = add i64 %call, %call1, !dbg !69
  %add2 = add i64 %add, 16, !dbg !70
  %call3 = call noalias i8* @malloc(i64 %add2) #6, !dbg !71
  store i8* %call3, i8** %result, align 8, !dbg !63
  call void @llvm.dbg.declare(metadata i8** %path2, metadata !73, metadata !30), !dbg !74
  call void @llvm.dbg.declare(metadata i8** %tmp, metadata !75, metadata !30), !dbg !76
  %2 = load i8*, i8** %result, align 8, !dbg !77
  %tobool = icmp ne i8* %2, null, !dbg !77
  br i1 %tobool, label %if.end, label %if.then, !dbg !79

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !80
  br label %return, !dbg !80

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %path.addr, align 8, !dbg !81
  %call4 = call noalias i8* @strdup(i8* %3) #6, !dbg !82
  store i8* %call4, i8** %path2, align 8, !dbg !83
  %4 = load i8*, i8** %path2, align 8, !dbg !84
  %tobool5 = icmp ne i8* %4, null, !dbg !84
  br i1 %tobool5, label %if.end7, label %if.then6, !dbg !86

if.then6:                                         ; preds = %if.end
  %5 = load i8*, i8** %result, align 8, !dbg !87
  call void @free(i8* %5) #6, !dbg !89
  store i8* null, i8** %retval, align 8, !dbg !90
  br label %return, !dbg !90

if.end7:                                          ; preds = %if.end
  %6 = load i8*, i8** %path.addr, align 8, !dbg !91
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 0, !dbg !91
  %7 = load i8, i8* %arrayidx, align 1, !dbg !91
  %conv = sext i8 %7 to i32, !dbg !91
  %cmp = icmp eq i32 %conv, 47, !dbg !93
  br i1 %cmp, label %if.then9, label %if.else, !dbg !94

if.then9:                                         ; preds = %if.end7
  %8 = load i8*, i8** %result, align 8, !dbg !95
  %call10 = call i8* @strcpy(i8* %8, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)) #6, !dbg !96
  br label %if.end12, !dbg !96

if.else:                                          ; preds = %if.end7
  %9 = load i8*, i8** %result, align 8, !dbg !97
  %10 = load i8*, i8** @cwd, align 8, !dbg !98
  %call11 = call i8* @strcpy(i8* %9, i8* %10) #6, !dbg !99
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.then9
  br label %while.cond, !dbg !100

while.cond:                                       ; preds = %if.end22, %if.end12
  %11 = load i8*, i8** %path2, align 8, !dbg !101
  %call13 = call i8* @strchr(i8* %11, i32 47) #7, !dbg !102
  %tobool14 = icmp ne i8* %call13, null, !dbg !103
  br i1 %tobool14, label %while.body, label %while.end, !dbg !103

while.body:                                       ; preds = %while.cond
  %12 = load i8*, i8** %path2, align 8, !dbg !104
  %call15 = call noalias i8* @strdup(i8* %12) #6, !dbg !106
  store i8* %call15, i8** %tmp, align 8, !dbg !107
  %13 = load i8*, i8** %tmp, align 8, !dbg !108
  %tobool16 = icmp ne i8* %13, null, !dbg !108
  br i1 %tobool16, label %if.then17, label %if.end22, !dbg !110

if.then17:                                        ; preds = %while.body
  %14 = load i8*, i8** %tmp, align 8, !dbg !111
  %call18 = call i8* @strchr(i8* %14, i32 47) #7, !dbg !113
  store i8 0, i8* %call18, align 1, !dbg !114
  %15 = load i8*, i8** %path2, align 8, !dbg !115
  %16 = load i8*, i8** %tmp, align 8, !dbg !116
  %call19 = call i64 @strlen(i8* %16) #7, !dbg !117
  %add20 = add i64 %call19, 1, !dbg !118
  %conv21 = trunc i64 %add20 to i32, !dbg !117
  call void @cutto(i8* %15, i32 %conv21), !dbg !119
  %17 = load i8*, i8** %result, align 8, !dbg !121
  %18 = load i8*, i8** %tmp, align 8, !dbg !122
  call void @appendpath(i8* %17, i8* %18), !dbg !123
  %19 = load i8*, i8** %tmp, align 8, !dbg !124
  call void @free(i8* %19) #6, !dbg !125
  br label %if.end22, !dbg !126

if.end22:                                         ; preds = %if.then17, %while.body
  br label %while.cond, !dbg !127

while.end:                                        ; preds = %while.cond
  %20 = load i8*, i8** %result, align 8, !dbg !128
  %21 = load i8*, i8** %path2, align 8, !dbg !129
  call void @appendpath(i8* %20, i8* %21), !dbg !130
  %22 = load i8*, i8** %path2, align 8, !dbg !131
  call void @free(i8* %22) #6, !dbg !132
  %23 = load i8*, i8** %result, align 8, !dbg !133
  store i8* %23, i8** %retval, align 8, !dbg !134
  br label %return, !dbg !134

return:                                           ; preds = %while.end, %if.then6, %if.then
  %24 = load i8*, i8** %retval, align 8, !dbg !135
  ret i8* %24, !dbg !135
}

; Function Attrs: nounwind
declare i32 @chdir(i8*) #2

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #3

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #2

declare void @new_umask(...) #5

; Function Attrs: nounwind uwtable
define i8* @bftpd_cwd_getcwd() #0 !dbg !11 {
entry:
  %retval = alloca i8*, align 8
  %0 = load i8*, i8** @cwd, align 8, !dbg !136
  %tobool = icmp ne i8* %0, null, !dbg !136
  br i1 %tobool, label %if.then, label %if.else, !dbg !138

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** @cwd, align 8, !dbg !139
  %call = call noalias i8* @strdup(i8* %1) #6, !dbg !140
  store i8* %call, i8** %retval, align 8, !dbg !141
  br label %return, !dbg !141

if.else:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !142
  br label %return, !dbg !142

return:                                           ; preds = %if.else, %if.then
  %2 = load i8*, i8** %retval, align 8, !dbg !143
  ret i8* %2, !dbg !143
}

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #2

; Function Attrs: nounwind uwtable
define void @appendpath(i8* %result, i8* %tmp) #0 !dbg !14 {
entry:
  %result.addr = alloca i8*, align 8
  %tmp.addr = alloca i8*, align 8
  store i8* %result, i8** %result.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %result.addr, metadata !144, metadata !30), !dbg !145
  store i8* %tmp, i8** %tmp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %tmp.addr, metadata !146, metadata !30), !dbg !147
  %0 = load i8*, i8** %tmp.addr, align 8, !dbg !148
  %call = call i32 @strcmp(i8* %0, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0)) #7, !dbg !150
  %tobool = icmp ne i32 %call, 0, !dbg !150
  br i1 %tobool, label %if.end, label %if.then, !dbg !151

if.then:                                          ; preds = %entry
  br label %if.end42, !dbg !152

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %tmp.addr, align 8, !dbg !153
  %call1 = call i32 @strcmp(i8* %1, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0)) #7, !dbg !155
  %tobool2 = icmp ne i32 %call1, 0, !dbg !155
  br i1 %tobool2, label %if.else, label %if.then3, !dbg !156

if.then3:                                         ; preds = %if.end
  %2 = load i8*, i8** %result.addr, align 8, !dbg !157
  %call4 = call i32 @strcmp(i8* %2, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)) #7, !dbg !160
  %tobool5 = icmp ne i32 %call4, 0, !dbg !160
  br i1 %tobool5, label %if.then6, label %if.end31, !dbg !161

if.then6:                                         ; preds = %if.then3
  %3 = load i8*, i8** %result.addr, align 8, !dbg !162
  %call7 = call i64 @strlen(i8* %3) #7, !dbg !165
  %sub = sub i64 %call7, 1, !dbg !166
  %4 = load i8*, i8** %result.addr, align 8, !dbg !167
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 %sub, !dbg !167
  %5 = load i8, i8* %arrayidx, align 1, !dbg !167
  %conv = sext i8 %5 to i32, !dbg !167
  %cmp = icmp eq i32 %conv, 47, !dbg !168
  br i1 %cmp, label %if.then9, label %if.end13, !dbg !169

if.then9:                                         ; preds = %if.then6
  %6 = load i8*, i8** %result.addr, align 8, !dbg !170
  %call10 = call i64 @strlen(i8* %6) #7, !dbg !171
  %sub11 = sub i64 %call10, 1, !dbg !172
  %7 = load i8*, i8** %result.addr, align 8, !dbg !173
  %arrayidx12 = getelementptr inbounds i8, i8* %7, i64 %sub11, !dbg !173
  store i8 0, i8* %arrayidx12, align 1, !dbg !174
  br label %if.end13, !dbg !173

if.end13:                                         ; preds = %if.then9, %if.then6
  %8 = load i8*, i8** %result.addr, align 8, !dbg !175
  store i8* %8, i8** %tmp.addr, align 8, !dbg !176
  br label %while.cond, !dbg !177

while.cond:                                       ; preds = %while.body, %if.end13
  %9 = load i8*, i8** %tmp.addr, align 8, !dbg !178
  %call14 = call i8* @strchr(i8* %9, i32 47) #7, !dbg !180
  %tobool15 = icmp ne i8* %call14, null, !dbg !181
  br i1 %tobool15, label %while.body, label %while.end, !dbg !181

while.body:                                       ; preds = %while.cond
  %10 = load i8*, i8** %tmp.addr, align 8, !dbg !182
  %call16 = call i8* @strchr(i8* %10, i32 47) #7, !dbg !183
  %add.ptr = getelementptr inbounds i8, i8* %call16, i64 1, !dbg !184
  store i8* %add.ptr, i8** %tmp.addr, align 8, !dbg !185
  br label %while.cond, !dbg !186

while.end:                                        ; preds = %while.cond
  %11 = load i8*, i8** %tmp.addr, align 8, !dbg !188
  store i8 0, i8* %11, align 1, !dbg !189
  %12 = load i8*, i8** %result.addr, align 8, !dbg !190
  %call17 = call i64 @strlen(i8* %12) #7, !dbg !192
  %sub18 = sub i64 %call17, 1, !dbg !193
  %13 = load i8*, i8** %result.addr, align 8, !dbg !194
  %arrayidx19 = getelementptr inbounds i8, i8* %13, i64 %sub18, !dbg !194
  %14 = load i8, i8* %arrayidx19, align 1, !dbg !194
  %conv20 = sext i8 %14 to i32, !dbg !194
  %cmp21 = icmp eq i32 %conv20, 47, !dbg !195
  br i1 %cmp21, label %land.lhs.true, label %if.end30, !dbg !196

land.lhs.true:                                    ; preds = %while.end
  %15 = load i8*, i8** %result.addr, align 8, !dbg !197
  %call23 = call i64 @strlen(i8* %15) #7, !dbg !199
  %cmp24 = icmp ugt i64 %call23, 1, !dbg !200
  br i1 %cmp24, label %if.then26, label %if.end30, !dbg !201

if.then26:                                        ; preds = %land.lhs.true
  %16 = load i8*, i8** %result.addr, align 8, !dbg !202
  %call27 = call i64 @strlen(i8* %16) #7, !dbg !203
  %sub28 = sub i64 %call27, 1, !dbg !204
  %17 = load i8*, i8** %result.addr, align 8, !dbg !205
  %arrayidx29 = getelementptr inbounds i8, i8* %17, i64 %sub28, !dbg !205
  store i8 0, i8* %arrayidx29, align 1, !dbg !206
  br label %if.end30, !dbg !205

if.end30:                                         ; preds = %if.then26, %land.lhs.true, %while.end
  br label %if.end31, !dbg !207

if.end31:                                         ; preds = %if.end30, %if.then3
  br label %if.end42, !dbg !208

if.else:                                          ; preds = %if.end
  %18 = load i8*, i8** %result.addr, align 8, !dbg !209
  %call32 = call i64 @strlen(i8* %18) #7, !dbg !212
  %sub33 = sub i64 %call32, 1, !dbg !213
  %19 = load i8*, i8** %result.addr, align 8, !dbg !214
  %arrayidx34 = getelementptr inbounds i8, i8* %19, i64 %sub33, !dbg !214
  %20 = load i8, i8* %arrayidx34, align 1, !dbg !214
  %conv35 = sext i8 %20 to i32, !dbg !214
  %cmp36 = icmp ne i32 %conv35, 47, !dbg !215
  br i1 %cmp36, label %if.then38, label %if.end40, !dbg !216

if.then38:                                        ; preds = %if.else
  %21 = load i8*, i8** %result.addr, align 8, !dbg !217
  %call39 = call i8* @strcat(i8* %21, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)) #6, !dbg !218
  br label %if.end40, !dbg !218

if.end40:                                         ; preds = %if.then38, %if.else
  %22 = load i8*, i8** %result.addr, align 8, !dbg !219
  %23 = load i8*, i8** %tmp.addr, align 8, !dbg !220
  %call41 = call i8* @strcat(i8* %22, i8* %23) #6, !dbg !221
  br label %if.end42

if.end42:                                         ; preds = %if.then, %if.end40, %if.end31
  ret void, !dbg !222
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #4

; Function Attrs: nounwind
declare i8* @strcat(i8*, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

declare void @cutto(i8*, i32) #5

; Function Attrs: nounwind uwtable
define void @bftpd_cwd_init() #0 !dbg !20 {
entry:
  %call = call noalias i8* @malloc(i64 256) #6, !dbg !223
  store i8* %call, i8** @cwd, align 8, !dbg !224
  %0 = load i8*, i8** @cwd, align 8, !dbg !225
  %call1 = call i8* @getcwd(i8* %0, i64 255) #6, !dbg !226
  ret void, !dbg !227
}

; Function Attrs: nounwind
declare i8* @getcwd(i8*, i64) #2

; Function Attrs: nounwind uwtable
define void @bftpd_cwd_end() #0 !dbg !23 {
entry:
  %0 = load i8*, i8** @cwd, align 8, !dbg !228
  %tobool = icmp ne i8* %0, null, !dbg !228
  br i1 %tobool, label %if.then, label %if.end, !dbg !230

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** @cwd, align 8, !dbg !231
  call void @free(i8* %1) #6, !dbg !233
  store i8* null, i8** @cwd, align 8, !dbg !234
  br label %if.end, !dbg !235

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !236
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!26, !27}
!llvm.ident = !{!28}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !24)
!1 = !DIFile(filename: "cwd.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{}
!3 = !{!4, !11, !14, !17, !20, !23}
!4 = distinct !DISubprogram(name: "bftpd_cwd_chdir", scope: !5, file: !5, line: 16, type: !6, isLocal: false, isDefinition: true, scopeLine: 17, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/cwd.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!6 = !DISubroutineType(types: !7)
!7 = !{!8, !9}
!8 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!11 = distinct !DISubprogram(name: "bftpd_cwd_getcwd", scope: !5, file: !5, line: 30, type: !12, isLocal: false, isDefinition: true, scopeLine: 31, isOptimized: false, variables: !2)
!12 = !DISubroutineType(types: !13)
!13 = !{!9}
!14 = distinct !DISubprogram(name: "appendpath", scope: !5, file: !5, line: 38, type: !15, isLocal: false, isDefinition: true, scopeLine: 39, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!15 = !DISubroutineType(types: !16)
!16 = !{null, !9, !9}
!17 = distinct !DISubprogram(name: "bftpd_cwd_mappath", scope: !5, file: !5, line: 62, type: !18, isLocal: false, isDefinition: true, scopeLine: 63, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!18 = !DISubroutineType(types: !19)
!19 = !{!9, !9}
!20 = distinct !DISubprogram(name: "bftpd_cwd_init", scope: !5, file: !5, line: 97, type: !21, isLocal: false, isDefinition: true, scopeLine: 98, isOptimized: false, variables: !2)
!21 = !DISubroutineType(types: !22)
!22 = !{null}
!23 = distinct !DISubprogram(name: "bftpd_cwd_end", scope: !5, file: !5, line: 103, type: !21, isLocal: false, isDefinition: true, scopeLine: 104, isOptimized: false, variables: !2)
!24 = !{!25}
!25 = !DIGlobalVariable(name: "cwd", scope: !0, file: !5, line: 14, type: !9, isLocal: false, isDefinition: true, variable: i8** @cwd)
!26 = !{i32 2, !"Dwarf Version", i32 4}
!27 = !{i32 2, !"Debug Info Version", i32 3}
!28 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!29 = !DILocalVariable(name: "dir", arg: 1, scope: !4, file: !5, line: 16, type: !9)
!30 = !DIExpression()
!31 = !DILocation(line: 16, column: 27, scope: !4)
!32 = !DILocalVariable(name: "tmp", scope: !4, file: !5, line: 18, type: !9)
!33 = !DILocation(line: 18, column: 8, scope: !4)
!34 = !DILocation(line: 18, column: 32, scope: !4)
!35 = !DILocation(line: 18, column: 14, scope: !4)
!36 = !DILocation(line: 19, column: 12, scope: !37)
!37 = distinct !DILexicalBlock(scope: !4, file: !5, line: 19, column: 6)
!38 = !DILocation(line: 19, column: 6, scope: !37)
!39 = !DILocation(line: 19, column: 6, scope: !4)
!40 = !DILocation(line: 20, column: 8, scope: !41)
!41 = distinct !DILexicalBlock(scope: !37, file: !5, line: 19, column: 18)
!42 = !DILocation(line: 20, column: 3, scope: !41)
!43 = !DILocation(line: 21, column: 10, scope: !41)
!44 = !DILocation(line: 21, column: 3, scope: !41)
!45 = !DILocation(line: 23, column: 16, scope: !4)
!46 = !DILocation(line: 23, column: 28, scope: !4)
!47 = !DILocation(line: 23, column: 21, scope: !4)
!48 = !DILocation(line: 23, column: 33, scope: !4)
!49 = !DILocation(line: 23, column: 8, scope: !50)
!50 = !DILexicalBlockFile(scope: !4, file: !5, discriminator: 1)
!51 = !DILocation(line: 23, column: 6, scope: !4)
!52 = !DILocation(line: 24, column: 9, scope: !4)
!53 = !DILocation(line: 24, column: 14, scope: !4)
!54 = !DILocation(line: 24, column: 2, scope: !4)
!55 = !DILocation(line: 25, column: 2, scope: !4)
!56 = !DILocation(line: 26, column: 7, scope: !4)
!57 = !DILocation(line: 26, column: 2, scope: !4)
!58 = !DILocation(line: 27, column: 2, scope: !4)
!59 = !DILocation(line: 28, column: 1, scope: !4)
!60 = !DILocalVariable(name: "path", arg: 1, scope: !17, file: !5, line: 62, type: !9)
!61 = !DILocation(line: 62, column: 31, scope: !17)
!62 = !DILocalVariable(name: "result", scope: !17, file: !5, line: 64, type: !9)
!63 = !DILocation(line: 64, column: 8, scope: !17)
!64 = !DILocation(line: 64, column: 31, scope: !17)
!65 = !DILocation(line: 64, column: 24, scope: !17)
!66 = !DILocation(line: 64, column: 46, scope: !17)
!67 = !DILocation(line: 64, column: 39, scope: !68)
!68 = !DILexicalBlockFile(scope: !17, file: !5, discriminator: 1)
!69 = !DILocation(line: 64, column: 37, scope: !17)
!70 = !DILocation(line: 64, column: 51, scope: !17)
!71 = !DILocation(line: 64, column: 17, scope: !72)
!72 = !DILexicalBlockFile(scope: !17, file: !5, discriminator: 2)
!73 = !DILocalVariable(name: "path2", scope: !17, file: !5, line: 65, type: !9)
!74 = !DILocation(line: 65, column: 8, scope: !17)
!75 = !DILocalVariable(name: "tmp", scope: !17, file: !5, line: 66, type: !9)
!76 = !DILocation(line: 66, column: 8, scope: !17)
!77 = !DILocation(line: 68, column: 15, scope: !78)
!78 = distinct !DILexicalBlock(scope: !17, file: !5, line: 68, column: 13)
!79 = !DILocation(line: 68, column: 13, scope: !17)
!80 = !DILocation(line: 69, column: 12, scope: !78)
!81 = !DILocation(line: 70, column: 24, scope: !17)
!82 = !DILocation(line: 70, column: 17, scope: !17)
!83 = !DILocation(line: 70, column: 15, scope: !17)
!84 = !DILocation(line: 71, column: 15, scope: !85)
!85 = distinct !DILexicalBlock(scope: !17, file: !5, line: 71, column: 13)
!86 = !DILocation(line: 71, column: 13, scope: !17)
!87 = !DILocation(line: 73, column: 17, scope: !88)
!88 = distinct !DILexicalBlock(scope: !85, file: !5, line: 72, column: 9)
!89 = !DILocation(line: 73, column: 12, scope: !88)
!90 = !DILocation(line: 74, column: 12, scope: !88)
!91 = !DILocation(line: 77, column: 6, scope: !92)
!92 = distinct !DILexicalBlock(scope: !17, file: !5, line: 77, column: 6)
!93 = !DILocation(line: 77, column: 14, scope: !92)
!94 = !DILocation(line: 77, column: 6, scope: !17)
!95 = !DILocation(line: 78, column: 10, scope: !92)
!96 = !DILocation(line: 78, column: 3, scope: !92)
!97 = !DILocation(line: 80, column: 10, scope: !92)
!98 = !DILocation(line: 80, column: 18, scope: !92)
!99 = !DILocation(line: 80, column: 3, scope: !92)
!100 = !DILocation(line: 82, column: 2, scope: !17)
!101 = !DILocation(line: 82, column: 16, scope: !68)
!102 = !DILocation(line: 82, column: 9, scope: !68)
!103 = !DILocation(line: 82, column: 2, scope: !68)
!104 = !DILocation(line: 83, column: 16, scope: !105)
!105 = distinct !DILexicalBlock(scope: !17, file: !5, line: 82, column: 29)
!106 = !DILocation(line: 83, column: 9, scope: !105)
!107 = !DILocation(line: 83, column: 7, scope: !105)
!108 = !DILocation(line: 84, column: 21, scope: !109)
!109 = distinct !DILexicalBlock(scope: !105, file: !5, line: 84, column: 21)
!110 = !DILocation(line: 84, column: 21, scope: !105)
!111 = !DILocation(line: 86, column: 13, scope: !112)
!112 = distinct !DILexicalBlock(scope: !109, file: !5, line: 85, column: 17)
!113 = !DILocation(line: 86, column: 6, scope: !112)
!114 = !DILocation(line: 86, column: 23, scope: !112)
!115 = !DILocation(line: 87, column: 11, scope: !112)
!116 = !DILocation(line: 87, column: 25, scope: !112)
!117 = !DILocation(line: 87, column: 18, scope: !112)
!118 = !DILocation(line: 87, column: 30, scope: !112)
!119 = !DILocation(line: 87, column: 5, scope: !120)
!120 = !DILexicalBlockFile(scope: !112, file: !5, discriminator: 1)
!121 = !DILocation(line: 88, column: 16, scope: !112)
!122 = !DILocation(line: 88, column: 24, scope: !112)
!123 = !DILocation(line: 88, column: 5, scope: !112)
!124 = !DILocation(line: 89, column: 10, scope: !112)
!125 = !DILocation(line: 89, column: 5, scope: !112)
!126 = !DILocation(line: 90, column: 17, scope: !112)
!127 = !DILocation(line: 82, column: 2, scope: !72)
!128 = !DILocation(line: 92, column: 13, scope: !17)
!129 = !DILocation(line: 92, column: 21, scope: !17)
!130 = !DILocation(line: 92, column: 2, scope: !17)
!131 = !DILocation(line: 93, column: 7, scope: !17)
!132 = !DILocation(line: 93, column: 2, scope: !17)
!133 = !DILocation(line: 94, column: 9, scope: !17)
!134 = !DILocation(line: 94, column: 2, scope: !17)
!135 = !DILocation(line: 95, column: 1, scope: !17)
!136 = !DILocation(line: 32, column: 11, scope: !137)
!137 = distinct !DILexicalBlock(scope: !11, file: !5, line: 32, column: 11)
!138 = !DILocation(line: 32, column: 11, scope: !11)
!139 = !DILocation(line: 33, column: 17, scope: !137)
!140 = !DILocation(line: 33, column: 10, scope: !137)
!141 = !DILocation(line: 33, column: 3, scope: !137)
!142 = !DILocation(line: 35, column: 10, scope: !137)
!143 = !DILocation(line: 36, column: 1, scope: !11)
!144 = !DILocalVariable(name: "result", arg: 1, scope: !14, file: !5, line: 38, type: !9)
!145 = !DILocation(line: 38, column: 23, scope: !14)
!146 = !DILocalVariable(name: "tmp", arg: 2, scope: !14, file: !5, line: 38, type: !9)
!147 = !DILocation(line: 38, column: 37, scope: !14)
!148 = !DILocation(line: 40, column: 14, scope: !149)
!149 = distinct !DILexicalBlock(scope: !14, file: !5, line: 40, column: 6)
!150 = !DILocation(line: 40, column: 7, scope: !149)
!151 = !DILocation(line: 40, column: 6, scope: !14)
!152 = !DILocation(line: 41, column: 3, scope: !149)
!153 = !DILocation(line: 42, column: 14, scope: !154)
!154 = distinct !DILexicalBlock(scope: !14, file: !5, line: 42, column: 6)
!155 = !DILocation(line: 42, column: 7, scope: !154)
!156 = !DILocation(line: 42, column: 6, scope: !14)
!157 = !DILocation(line: 43, column: 20, scope: !158)
!158 = distinct !DILexicalBlock(scope: !159, file: !5, line: 43, column: 13)
!159 = distinct !DILexicalBlock(scope: !154, file: !5, line: 42, column: 26)
!160 = !DILocation(line: 43, column: 13, scope: !158)
!161 = !DILocation(line: 43, column: 13, scope: !159)
!162 = !DILocation(line: 44, column: 31, scope: !163)
!163 = distinct !DILexicalBlock(scope: !164, file: !5, line: 44, column: 17)
!164 = distinct !DILexicalBlock(scope: !158, file: !5, line: 43, column: 34)
!165 = !DILocation(line: 44, column: 24, scope: !163)
!166 = !DILocation(line: 44, column: 39, scope: !163)
!167 = !DILocation(line: 44, column: 17, scope: !163)
!168 = !DILocation(line: 44, column: 44, scope: !163)
!169 = !DILocation(line: 44, column: 17, scope: !164)
!170 = !DILocation(line: 45, column: 31, scope: !163)
!171 = !DILocation(line: 45, column: 24, scope: !163)
!172 = !DILocation(line: 45, column: 39, scope: !163)
!173 = !DILocation(line: 45, column: 17, scope: !163)
!174 = !DILocation(line: 45, column: 44, scope: !163)
!175 = !DILocation(line: 46, column: 19, scope: !164)
!176 = !DILocation(line: 46, column: 17, scope: !164)
!177 = !DILocation(line: 47, column: 13, scope: !164)
!178 = !DILocation(line: 47, column: 27, scope: !179)
!179 = !DILexicalBlockFile(scope: !164, file: !5, discriminator: 1)
!180 = !DILocation(line: 47, column: 20, scope: !179)
!181 = !DILocation(line: 47, column: 13, scope: !179)
!182 = !DILocation(line: 48, column: 30, scope: !164)
!183 = !DILocation(line: 48, column: 23, scope: !164)
!184 = !DILocation(line: 48, column: 40, scope: !164)
!185 = !DILocation(line: 48, column: 21, scope: !164)
!186 = !DILocation(line: 47, column: 13, scope: !187)
!187 = !DILexicalBlockFile(scope: !164, file: !5, discriminator: 2)
!188 = !DILocation(line: 49, column: 14, scope: !164)
!189 = !DILocation(line: 49, column: 18, scope: !164)
!190 = !DILocation(line: 50, column: 32, scope: !191)
!191 = distinct !DILexicalBlock(scope: !164, file: !5, line: 50, column: 17)
!192 = !DILocation(line: 50, column: 25, scope: !191)
!193 = !DILocation(line: 50, column: 40, scope: !191)
!194 = !DILocation(line: 50, column: 18, scope: !191)
!195 = !DILocation(line: 50, column: 45, scope: !191)
!196 = !DILocation(line: 50, column: 53, scope: !191)
!197 = !DILocation(line: 50, column: 64, scope: !198)
!198 = !DILexicalBlockFile(scope: !191, file: !5, discriminator: 1)
!199 = !DILocation(line: 50, column: 57, scope: !198)
!200 = !DILocation(line: 50, column: 72, scope: !198)
!201 = !DILocation(line: 50, column: 17, scope: !198)
!202 = !DILocation(line: 51, column: 31, scope: !191)
!203 = !DILocation(line: 51, column: 24, scope: !191)
!204 = !DILocation(line: 51, column: 39, scope: !191)
!205 = !DILocation(line: 51, column: 17, scope: !191)
!206 = !DILocation(line: 51, column: 44, scope: !191)
!207 = !DILocation(line: 52, column: 9, scope: !164)
!208 = !DILocation(line: 53, column: 2, scope: !159)
!209 = !DILocation(line: 54, column: 21, scope: !210)
!210 = distinct !DILexicalBlock(scope: !211, file: !5, line: 54, column: 7)
!211 = distinct !DILexicalBlock(scope: !154, file: !5, line: 53, column: 9)
!212 = !DILocation(line: 54, column: 14, scope: !210)
!213 = !DILocation(line: 54, column: 29, scope: !210)
!214 = !DILocation(line: 54, column: 7, scope: !210)
!215 = !DILocation(line: 54, column: 34, scope: !210)
!216 = !DILocation(line: 54, column: 7, scope: !211)
!217 = !DILocation(line: 55, column: 11, scope: !210)
!218 = !DILocation(line: 55, column: 4, scope: !210)
!219 = !DILocation(line: 56, column: 10, scope: !211)
!220 = !DILocation(line: 56, column: 18, scope: !211)
!221 = !DILocation(line: 56, column: 3, scope: !211)
!222 = !DILocation(line: 58, column: 1, scope: !14)
!223 = !DILocation(line: 99, column: 8, scope: !20)
!224 = !DILocation(line: 99, column: 6, scope: !20)
!225 = !DILocation(line: 100, column: 9, scope: !20)
!226 = !DILocation(line: 100, column: 2, scope: !20)
!227 = !DILocation(line: 101, column: 1, scope: !20)
!228 = !DILocation(line: 105, column: 6, scope: !229)
!229 = distinct !DILexicalBlock(scope: !23, file: !5, line: 105, column: 6)
!230 = !DILocation(line: 105, column: 6, scope: !23)
!231 = !DILocation(line: 106, column: 8, scope: !232)
!232 = distinct !DILexicalBlock(scope: !229, file: !5, line: 105, column: 11)
!233 = !DILocation(line: 106, column: 3, scope: !232)
!234 = !DILocation(line: 107, column: 7, scope: !232)
!235 = !DILocation(line: 108, column: 2, scope: !232)
!236 = !DILocation(line: 109, column: 1, scope: !23)
