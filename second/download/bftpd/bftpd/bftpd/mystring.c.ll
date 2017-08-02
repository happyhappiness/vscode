; ModuleID = '/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/mystring.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [2 x i8] c",\00", align 1

; Function Attrs: nounwind uwtable
define i32 @pos(i8* %haystack, i8* %needle) #0 !dbg !8 {
entry:
  %retval = alloca i32, align 4
  %haystack.addr = alloca i8*, align 8
  %needle.addr = alloca i8*, align 8
  store i8* %haystack, i8** %haystack.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %haystack.addr, metadata !27, metadata !28), !dbg !29
  store i8* %needle, i8** %needle.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %needle.addr, metadata !30, metadata !28), !dbg !31
  %0 = load i8*, i8** %haystack.addr, align 8, !dbg !32
  %1 = load i8*, i8** %needle.addr, align 8, !dbg !34
  %call = call i8* @strstr(i8* %0, i8* %1) #5, !dbg !35
  %tobool = icmp ne i8* %call, null, !dbg !35
  br i1 %tobool, label %if.then, label %if.else, !dbg !36

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %haystack.addr, align 8, !dbg !37
  %3 = load i8*, i8** %needle.addr, align 8, !dbg !39
  %call1 = call i8* @strstr(i8* %2, i8* %3) #5, !dbg !40
  %4 = ptrtoint i8* %call1 to i32, !dbg !41
  %5 = load i8*, i8** %haystack.addr, align 8, !dbg !42
  %6 = ptrtoint i8* %5 to i32, !dbg !43
  %sub = sub nsw i32 %4, %6, !dbg !44
  store i32 %sub, i32* %retval, align 4, !dbg !45
  br label %return, !dbg !45

if.else:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !46
  br label %return, !dbg !46

return:                                           ; preds = %if.else, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !48
  ret i32 %7, !dbg !48
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i8* @strstr(i8*, i8*) #2

; Function Attrs: nounwind uwtable
define void @cutto(i8* %str, i32 %len) #0 !dbg !12 {
entry:
  %str.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !49, metadata !28), !dbg !50
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !51, metadata !28), !dbg !52
  %0 = load i8*, i8** %str.addr, align 8, !dbg !53
  %1 = load i8*, i8** %str.addr, align 8, !dbg !54
  %2 = load i32, i32* %len.addr, align 4, !dbg !55
  %idx.ext = sext i32 %2 to i64, !dbg !56
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %idx.ext, !dbg !56
  %3 = load i8*, i8** %str.addr, align 8, !dbg !57
  %call = call i64 @strlen(i8* %3) #5, !dbg !58
  %4 = load i32, i32* %len.addr, align 4, !dbg !59
  %conv = sext i32 %4 to i64, !dbg !59
  %sub = sub i64 %call, %conv, !dbg !60
  %add = add i64 %sub, 1, !dbg !61
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %0, i8* %add.ptr, i64 %add, i32 1, i1 false), !dbg !62
  ret void, !dbg !64
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define void @mystrncpy(i8* %dest, i8* %src, i32 %len) #0 !dbg !15 {
entry:
  %dest.addr = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !65, metadata !28), !dbg !66
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !67, metadata !28), !dbg !68
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !69, metadata !28), !dbg !70
  %0 = load i8*, i8** %dest.addr, align 8, !dbg !71
  %1 = load i8*, i8** %src.addr, align 8, !dbg !72
  %2 = load i32, i32* %len.addr, align 4, !dbg !73
  %conv = sext i32 %2 to i64, !dbg !73
  %call = call i8* @strncpy(i8* %0, i8* %1, i64 %conv) #6, !dbg !74
  %3 = load i8*, i8** %dest.addr, align 8, !dbg !75
  %4 = load i32, i32* %len.addr, align 4, !dbg !76
  %idx.ext = sext i32 %4 to i64, !dbg !77
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 %idx.ext, !dbg !77
  store i8 0, i8* %add.ptr, align 1, !dbg !78
  ret void, !dbg !79
}

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #4

; Function Attrs: nounwind uwtable
define i32 @replace(i8* %str, i8* %what, i8* %by, i32 %max_length) #0 !dbg !18 {
entry:
  %retval = alloca i32, align 4
  %str.addr = alloca i8*, align 8
  %what.addr = alloca i8*, align 8
  %by.addr = alloca i8*, align 8
  %max_length.addr = alloca i32, align 4
  %foo = alloca i8*, align 8
  %bar = alloca i8*, align 8
  %i = alloca i32, align 4
  %str_length = alloca i32, align 4
  %what_length = alloca i32, align 4
  %by_length = alloca i32, align 4
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !80, metadata !28), !dbg !81
  store i8* %what, i8** %what.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %what.addr, metadata !82, metadata !28), !dbg !83
  store i8* %by, i8** %by.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %by.addr, metadata !84, metadata !28), !dbg !85
  store i32 %max_length, i32* %max_length.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %max_length.addr, metadata !86, metadata !28), !dbg !87
  call void @llvm.dbg.declare(metadata i8** %foo, metadata !88, metadata !28), !dbg !89
  call void @llvm.dbg.declare(metadata i8** %bar, metadata !90, metadata !28), !dbg !91
  %0 = load i8*, i8** %str.addr, align 8, !dbg !92
  store i8* %0, i8** %bar, align 8, !dbg !91
  call void @llvm.dbg.declare(metadata i32* %i, metadata !93, metadata !28), !dbg !94
  store i32 0, i32* %i, align 4, !dbg !94
  call void @llvm.dbg.declare(metadata i32* %str_length, metadata !95, metadata !28), !dbg !96
  call void @llvm.dbg.declare(metadata i32* %what_length, metadata !97, metadata !28), !dbg !98
  call void @llvm.dbg.declare(metadata i32* %by_length, metadata !99, metadata !28), !dbg !100
  %1 = load i8*, i8** %str.addr, align 8, !dbg !101
  %tobool = icmp ne i8* %1, null, !dbg !101
  br i1 %tobool, label %if.end, label %if.then, !dbg !103

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !104
  br label %return, !dbg !104

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %what.addr, align 8, !dbg !106
  %tobool1 = icmp ne i8* %2, null, !dbg !106
  br i1 %tobool1, label %if.end3, label %if.then2, !dbg !108

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !109
  br label %return, !dbg !109

if.end3:                                          ; preds = %if.end
  %3 = load i8*, i8** %by.addr, align 8, !dbg !111
  %tobool4 = icmp ne i8* %3, null, !dbg !111
  br i1 %tobool4, label %if.end6, label %if.then5, !dbg !113

if.then5:                                         ; preds = %if.end3
  store i32 0, i32* %retval, align 4, !dbg !114
  br label %return, !dbg !114

if.end6:                                          ; preds = %if.end3
  %4 = load i8*, i8** %what.addr, align 8, !dbg !116
  %call = call i64 @strlen(i8* %4) #5, !dbg !117
  %conv = trunc i64 %call to i32, !dbg !117
  store i32 %conv, i32* %what_length, align 4, !dbg !118
  %5 = load i8*, i8** %by.addr, align 8, !dbg !119
  %call7 = call i64 @strlen(i8* %5) #5, !dbg !120
  %conv8 = trunc i64 %call7 to i32, !dbg !120
  store i32 %conv8, i32* %by_length, align 4, !dbg !121
  %6 = load i8*, i8** %str.addr, align 8, !dbg !122
  %call9 = call i64 @strlen(i8* %6) #5, !dbg !123
  %conv10 = trunc i64 %call9 to i32, !dbg !123
  store i32 %conv10, i32* %str_length, align 4, !dbg !124
  %7 = load i8*, i8** %bar, align 8, !dbg !125
  %8 = load i8*, i8** %what.addr, align 8, !dbg !126
  %call11 = call i8* @strstr(i8* %7, i8* %8) #5, !dbg !127
  store i8* %call11, i8** %foo, align 8, !dbg !128
  br label %while.cond, !dbg !129

while.cond:                                       ; preds = %while.body, %if.end6
  %9 = load i8*, i8** %foo, align 8, !dbg !130
  %tobool12 = icmp ne i8* %9, null, !dbg !132
  br i1 %tobool12, label %land.rhs, label %land.end, !dbg !133

land.rhs:                                         ; preds = %while.cond
  %10 = load i32, i32* %str_length, align 4, !dbg !134
  %11 = load i32, i32* %by_length, align 4, !dbg !135
  %add = add nsw i32 %10, %11, !dbg !136
  %12 = load i32, i32* %what_length, align 4, !dbg !137
  %sub = sub nsw i32 %add, %12, !dbg !138
  %13 = load i32, i32* %max_length.addr, align 4, !dbg !139
  %sub13 = sub nsw i32 %13, 1, !dbg !140
  %cmp = icmp slt i32 %sub, %sub13, !dbg !141
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %14 = phi i1 [ false, %while.cond ], [ %cmp, %land.rhs ]
  br i1 %14, label %while.body, label %while.end, !dbg !142

while.body:                                       ; preds = %land.end
  %15 = load i8*, i8** %foo, align 8, !dbg !144
  %16 = load i8*, i8** %by.addr, align 8, !dbg !146
  %call15 = call i64 @strlen(i8* %16) #5, !dbg !147
  %add.ptr = getelementptr inbounds i8, i8* %15, i64 %call15, !dbg !148
  store i8* %add.ptr, i8** %bar, align 8, !dbg !149
  %17 = load i8*, i8** %bar, align 8, !dbg !150
  %18 = load i8*, i8** %foo, align 8, !dbg !151
  %19 = load i8*, i8** %what.addr, align 8, !dbg !152
  %call16 = call i64 @strlen(i8* %19) #5, !dbg !153
  %add.ptr17 = getelementptr inbounds i8, i8* %18, i64 %call16, !dbg !154
  %20 = load i8*, i8** %foo, align 8, !dbg !155
  %21 = load i8*, i8** %what.addr, align 8, !dbg !156
  %call18 = call i64 @strlen(i8* %21) #5, !dbg !157
  %add.ptr19 = getelementptr inbounds i8, i8* %20, i64 %call18, !dbg !159
  %call20 = call i64 @strlen(i8* %add.ptr19) #5, !dbg !160
  %add21 = add i64 %call20, 1, !dbg !162
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %17, i8* %add.ptr17, i64 %add21, i32 1, i1 false), !dbg !163
  %22 = load i8*, i8** %foo, align 8, !dbg !165
  %23 = load i8*, i8** %by.addr, align 8, !dbg !166
  %24 = load i8*, i8** %by.addr, align 8, !dbg !167
  %call22 = call i64 @strlen(i8* %24) #5, !dbg !168
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %22, i8* %23, i64 %call22, i32 1, i1 false), !dbg !169
  %25 = load i32, i32* %i, align 4, !dbg !170
  %inc = add nsw i32 %25, 1, !dbg !170
  store i32 %inc, i32* %i, align 4, !dbg !170
  %26 = load i8*, i8** %bar, align 8, !dbg !171
  %27 = load i8*, i8** %what.addr, align 8, !dbg !172
  %call23 = call i8* @strstr(i8* %26, i8* %27) #5, !dbg !173
  store i8* %call23, i8** %foo, align 8, !dbg !174
  %28 = load i8*, i8** %str.addr, align 8, !dbg !175
  %call24 = call i64 @strlen(i8* %28) #5, !dbg !176
  %conv25 = trunc i64 %call24 to i32, !dbg !176
  store i32 %conv25, i32* %str_length, align 4, !dbg !177
  br label %while.cond, !dbg !178

while.end:                                        ; preds = %land.end
  %29 = load i32, i32* %i, align 4, !dbg !180
  store i32 %29, i32* %retval, align 4, !dbg !181
  br label %return, !dbg !181

return:                                           ; preds = %while.end, %if.then5, %if.then2, %if.then
  %30 = load i32, i32* %retval, align 4, !dbg !182
  ret i32 %30, !dbg !182
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind uwtable
define i32 @int_from_list(i8* %list, i32 %n) #0 !dbg !21 {
entry:
  %retval = alloca i32, align 4
  %list.addr = alloca i8*, align 8
  %n.addr = alloca i32, align 4
  %str = alloca i8*, align 8
  %tok = alloca i8*, align 8
  %count = alloca i32, align 4
  %firstrun = alloca i32, align 4
  %start = alloca i8*, align 8
  %end = alloca i8*, align 8
  %s = alloca i32, align 4
  %e = alloca i32, align 4
  %val = alloca i32, align 4
  store i8* %list, i8** %list.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %list.addr, metadata !183, metadata !28), !dbg !184
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !185, metadata !28), !dbg !186
  call void @llvm.dbg.declare(metadata i8** %str, metadata !187, metadata !28), !dbg !188
  call void @llvm.dbg.declare(metadata i8** %tok, metadata !189, metadata !28), !dbg !190
  call void @llvm.dbg.declare(metadata i32* %count, metadata !191, metadata !28), !dbg !192
  store i32 -1, i32* %count, align 4, !dbg !192
  call void @llvm.dbg.declare(metadata i32* %firstrun, metadata !193, metadata !28), !dbg !194
  store i32 1, i32* %firstrun, align 4, !dbg !194
  %0 = load i8*, i8** %list.addr, align 8, !dbg !195
  %call = call i64 @strlen(i8* %0) #5, !dbg !196
  %add = add i64 %call, 2, !dbg !197
  %mul = mul i64 1, %add, !dbg !198
  %call1 = call noalias i8* @malloc(i64 %mul) #6, !dbg !199
  store i8* %call1, i8** %str, align 8, !dbg !201
  %1 = load i8*, i8** %str, align 8, !dbg !202
  %tobool = icmp ne i8* %1, null, !dbg !202
  br i1 %tobool, label %if.end, label %if.then, !dbg !204

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !205
  br label %return, !dbg !205

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %str, align 8, !dbg !206
  %3 = load i8*, i8** %list.addr, align 8, !dbg !207
  %call2 = call i64 @strlen(i8* %3) #5, !dbg !208
  %add3 = add i64 %call2, 2, !dbg !209
  call void @llvm.memset.p0i8.i64(i8* %2, i8 0, i64 %add3, i32 1, i1 false), !dbg !210
  %4 = load i8*, i8** %str, align 8, !dbg !211
  %5 = load i8*, i8** %list.addr, align 8, !dbg !212
  %6 = load i8*, i8** %list.addr, align 8, !dbg !213
  %call4 = call i64 @strlen(i8* %6) #5, !dbg !214
  %call5 = call i8* @strncpy(i8* %4, i8* %5, i64 %call4) #6, !dbg !215
  %7 = load i8*, i8** %list.addr, align 8, !dbg !216
  %call6 = call i64 @strlen(i8* %7) #5, !dbg !217
  %8 = load i8*, i8** %str, align 8, !dbg !218
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 %call6, !dbg !218
  store i8 44, i8* %arrayidx, align 1, !dbg !219
  br label %for.cond, !dbg !220

for.cond:                                         ; preds = %if.end51, %if.end
  %9 = load i32, i32* %firstrun, align 4, !dbg !221
  %tobool7 = icmp ne i32 %9, 0, !dbg !221
  br i1 %tobool7, label %if.then8, label %if.else, !dbg !226

if.then8:                                         ; preds = %for.cond
  %10 = load i8*, i8** %str, align 8, !dbg !227
  %call9 = call i8* @strtok(i8* %10, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0)) #6, !dbg !228
  store i8* %call9, i8** %tok, align 8, !dbg !229
  br label %if.end11, !dbg !230

if.else:                                          ; preds = %for.cond
  %call10 = call i8* @strtok(i8* null, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0)) #6, !dbg !231
  store i8* %call10, i8** %tok, align 8, !dbg !232
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then8
  %11 = load i8*, i8** %tok, align 8, !dbg !233
  %tobool12 = icmp ne i8* %11, null, !dbg !233
  br i1 %tobool12, label %lor.lhs.false, label %if.then14, !dbg !235

lor.lhs.false:                                    ; preds = %if.end11
  %12 = load i8*, i8** %tok, align 8, !dbg !236
  %13 = load i8, i8* %12, align 1, !dbg !238
  %conv = sext i8 %13 to i32, !dbg !238
  %cmp = icmp eq i32 %conv, 0, !dbg !239
  br i1 %cmp, label %if.then14, label %if.end15, !dbg !240

if.then14:                                        ; preds = %lor.lhs.false, %if.end11
  %14 = load i8*, i8** %str, align 8, !dbg !241
  call void @free(i8* %14) #6, !dbg !243
  store i32 -1, i32* %retval, align 4, !dbg !244
  br label %return, !dbg !244

if.end15:                                         ; preds = %lor.lhs.false
  %15 = load i8*, i8** %tok, align 8, !dbg !245
  %call16 = call i8* @strchr(i8* %15, i32 45) #5, !dbg !247
  %tobool17 = icmp ne i8* %call16, null, !dbg !247
  br i1 %tobool17, label %if.then18, label %if.else45, !dbg !248

if.then18:                                        ; preds = %if.end15
  call void @llvm.dbg.declare(metadata i8** %start, metadata !249, metadata !28), !dbg !251
  call void @llvm.dbg.declare(metadata i8** %end, metadata !252, metadata !28), !dbg !253
  call void @llvm.dbg.declare(metadata i32* %s, metadata !254, metadata !28), !dbg !255
  call void @llvm.dbg.declare(metadata i32* %e, metadata !256, metadata !28), !dbg !257
  %16 = load i8*, i8** %tok, align 8, !dbg !258
  store i8* %16, i8** %start, align 8, !dbg !259
  %17 = load i8*, i8** %tok, align 8, !dbg !260
  %call19 = call i8* @strchr(i8* %17, i32 45) #5, !dbg !261
  store i8* %call19, i8** %end, align 8, !dbg !262
  %18 = load i8*, i8** %end, align 8, !dbg !263
  store i8 0, i8* %18, align 1, !dbg !264
  %19 = load i8*, i8** %end, align 8, !dbg !265
  %incdec.ptr = getelementptr inbounds i8, i8* %19, i32 1, !dbg !265
  store i8* %incdec.ptr, i8** %end, align 8, !dbg !265
  %20 = load i8*, i8** %start, align 8, !dbg !266
  %21 = load i8, i8* %20, align 1, !dbg !268
  %tobool20 = icmp ne i8 %21, 0, !dbg !268
  br i1 %tobool20, label %lor.lhs.false21, label %if.then23, !dbg !269

lor.lhs.false21:                                  ; preds = %if.then18
  %22 = load i8*, i8** %end, align 8, !dbg !270
  %23 = load i8, i8* %22, align 1, !dbg !272
  %tobool22 = icmp ne i8 %23, 0, !dbg !272
  br i1 %tobool22, label %if.end24, label %if.then23, !dbg !273

if.then23:                                        ; preds = %lor.lhs.false21, %if.then18
  %24 = load i8*, i8** %str, align 8, !dbg !274
  call void @free(i8* %24) #6, !dbg !276
  store i32 -1, i32* %retval, align 4, !dbg !277
  br label %return, !dbg !277

if.end24:                                         ; preds = %lor.lhs.false21
  %25 = load i8*, i8** %start, align 8, !dbg !278
  %call25 = call i32 @atoi(i8* %25) #5, !dbg !279
  store i32 %call25, i32* %s, align 4, !dbg !280
  %26 = load i8*, i8** %end, align 8, !dbg !281
  %call26 = call i32 @atoi(i8* %26) #5, !dbg !282
  store i32 %call26, i32* %e, align 4, !dbg !283
  %27 = load i32, i32* %s, align 4, !dbg !284
  %cmp27 = icmp slt i32 %27, 1, !dbg !286
  br i1 %cmp27, label %if.then35, label %lor.lhs.false29, !dbg !287

lor.lhs.false29:                                  ; preds = %if.end24
  %28 = load i32, i32* %e, align 4, !dbg !288
  %cmp30 = icmp slt i32 %28, 1, !dbg !290
  br i1 %cmp30, label %if.then35, label %lor.lhs.false32, !dbg !291

lor.lhs.false32:                                  ; preds = %lor.lhs.false29
  %29 = load i32, i32* %e, align 4, !dbg !292
  %30 = load i32, i32* %s, align 4, !dbg !294
  %cmp33 = icmp slt i32 %29, %30, !dbg !295
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !296

if.then35:                                        ; preds = %lor.lhs.false32, %lor.lhs.false29, %if.end24
  %31 = load i8*, i8** %str, align 8, !dbg !297
  call void @free(i8* %31) #6, !dbg !299
  store i32 -1, i32* %retval, align 4, !dbg !300
  br label %return, !dbg !300

if.end36:                                         ; preds = %lor.lhs.false32
  %32 = load i32, i32* %e, align 4, !dbg !301
  %33 = load i32, i32* %s, align 4, !dbg !302
  %sub = sub nsw i32 %32, %33, !dbg !303
  %add37 = add nsw i32 %sub, 1, !dbg !304
  %34 = load i32, i32* %count, align 4, !dbg !305
  %add38 = add nsw i32 %34, %add37, !dbg !305
  store i32 %add38, i32* %count, align 4, !dbg !305
  %35 = load i32, i32* %count, align 4, !dbg !306
  %36 = load i32, i32* %n.addr, align 4, !dbg !308
  %cmp39 = icmp sge i32 %35, %36, !dbg !309
  br i1 %cmp39, label %if.then41, label %if.end44, !dbg !310

if.then41:                                        ; preds = %if.end36
  %37 = load i8*, i8** %str, align 8, !dbg !311
  call void @free(i8* %37) #6, !dbg !313
  %38 = load i32, i32* %e, align 4, !dbg !314
  %39 = load i32, i32* %count, align 4, !dbg !315
  %40 = load i32, i32* %n.addr, align 4, !dbg !316
  %sub42 = sub nsw i32 %39, %40, !dbg !317
  %sub43 = sub nsw i32 %38, %sub42, !dbg !318
  store i32 %sub43, i32* %retval, align 4, !dbg !319
  br label %return, !dbg !319

if.end44:                                         ; preds = %if.end36
  br label %if.end51, !dbg !320

if.else45:                                        ; preds = %if.end15
  %41 = load i32, i32* %count, align 4, !dbg !321
  %inc = add nsw i32 %41, 1, !dbg !321
  store i32 %inc, i32* %count, align 4, !dbg !321
  %42 = load i32, i32* %count, align 4, !dbg !323
  %43 = load i32, i32* %n.addr, align 4, !dbg !325
  %cmp46 = icmp eq i32 %42, %43, !dbg !326
  br i1 %cmp46, label %if.then48, label %if.end50, !dbg !327

if.then48:                                        ; preds = %if.else45
  call void @llvm.dbg.declare(metadata i32* %val, metadata !328, metadata !28), !dbg !330
  %44 = load i8*, i8** %tok, align 8, !dbg !331
  %call49 = call i32 @atoi(i8* %44) #5, !dbg !332
  store i32 %call49, i32* %val, align 4, !dbg !330
  %45 = load i8*, i8** %str, align 8, !dbg !333
  call void @free(i8* %45) #6, !dbg !334
  %46 = load i32, i32* %val, align 4, !dbg !335
  store i32 %46, i32* %retval, align 4, !dbg !336
  br label %return, !dbg !336

if.end50:                                         ; preds = %if.else45
  br label %if.end51

if.end51:                                         ; preds = %if.end50, %if.end44
  store i32 0, i32* %firstrun, align 4, !dbg !337
  br label %for.cond, !dbg !338

return:                                           ; preds = %if.then48, %if.then41, %if.then35, %if.then23, %if.then14, %if.then
  %47 = load i32, i32* %retval, align 4, !dbg !340
  ret i32 %47, !dbg !340
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

; Function Attrs: nounwind
declare i8* @strtok(i8*, i8*) #4

; Function Attrs: nounwind
declare void @free(i8*) #4

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #2

; Function Attrs: nounwind readonly
declare i32 @atoi(i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly }
attributes #6 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!24, !25}
!llvm.ident = !{!26}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !7)
!1 = !DIFile(filename: "mystring.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!7 = !{!8, !12, !15, !18, !21}
!8 = distinct !DISubprogram(name: "pos", scope: !9, file: !9, line: 5, type: !10, isLocal: false, isDefinition: true, scopeLine: 6, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = !DIFile(filename: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/mystring.c", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd")
!10 = !DISubroutineType(types: !11)
!11 = !{!4, !5, !5}
!12 = distinct !DISubprogram(name: "cutto", scope: !9, file: !9, line: 14, type: !13, isLocal: false, isDefinition: true, scopeLine: 15, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!13 = !DISubroutineType(types: !14)
!14 = !{null, !5, !4}
!15 = distinct !DISubprogram(name: "mystrncpy", scope: !9, file: !9, line: 19, type: !16, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!16 = !DISubroutineType(types: !17)
!17 = !{null, !5, !5, !4}
!18 = distinct !DISubprogram(name: "replace", scope: !9, file: !9, line: 30, type: !19, isLocal: false, isDefinition: true, scopeLine: 31, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!19 = !DISubroutineType(types: !20)
!20 = !{!4, !5, !5, !5, !4}
!21 = distinct !DISubprogram(name: "int_from_list", scope: !9, file: !9, line: 67, type: !22, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!22 = !DISubroutineType(types: !23)
!23 = !{!4, !5, !4}
!24 = !{i32 2, !"Dwarf Version", i32 4}
!25 = !{i32 2, !"Debug Info Version", i32 3}
!26 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!27 = !DILocalVariable(name: "haystack", arg: 1, scope: !8, file: !9, line: 5, type: !5)
!28 = !DIExpression()
!29 = !DILocation(line: 5, column: 15, scope: !8)
!30 = !DILocalVariable(name: "needle", arg: 2, scope: !8, file: !9, line: 5, type: !5)
!31 = !DILocation(line: 5, column: 31, scope: !8)
!32 = !DILocation(line: 7, column: 13, scope: !33)
!33 = distinct !DILexicalBlock(scope: !8, file: !9, line: 7, column: 6)
!34 = !DILocation(line: 7, column: 23, scope: !33)
!35 = !DILocation(line: 7, column: 6, scope: !33)
!36 = !DILocation(line: 7, column: 6, scope: !8)
!37 = !DILocation(line: 8, column: 23, scope: !38)
!38 = distinct !DILexicalBlock(scope: !33, file: !9, line: 7, column: 32)
!39 = !DILocation(line: 8, column: 33, scope: !38)
!40 = !DILocation(line: 8, column: 16, scope: !38)
!41 = !DILocation(line: 8, column: 10, scope: !38)
!42 = !DILocation(line: 8, column: 49, scope: !38)
!43 = !DILocation(line: 8, column: 43, scope: !38)
!44 = !DILocation(line: 8, column: 41, scope: !38)
!45 = !DILocation(line: 8, column: 3, scope: !38)
!46 = !DILocation(line: 10, column: 3, scope: !47)
!47 = distinct !DILexicalBlock(scope: !33, file: !9, line: 9, column: 9)
!48 = !DILocation(line: 12, column: 1, scope: !8)
!49 = !DILocalVariable(name: "str", arg: 1, scope: !12, file: !9, line: 14, type: !5)
!50 = !DILocation(line: 14, column: 18, scope: !12)
!51 = !DILocalVariable(name: "len", arg: 2, scope: !12, file: !9, line: 14, type: !4)
!52 = !DILocation(line: 14, column: 27, scope: !12)
!53 = !DILocation(line: 16, column: 10, scope: !12)
!54 = !DILocation(line: 16, column: 15, scope: !12)
!55 = !DILocation(line: 16, column: 21, scope: !12)
!56 = !DILocation(line: 16, column: 19, scope: !12)
!57 = !DILocation(line: 16, column: 33, scope: !12)
!58 = !DILocation(line: 16, column: 26, scope: !12)
!59 = !DILocation(line: 16, column: 40, scope: !12)
!60 = !DILocation(line: 16, column: 38, scope: !12)
!61 = !DILocation(line: 16, column: 44, scope: !12)
!62 = !DILocation(line: 16, column: 2, scope: !63)
!63 = !DILexicalBlockFile(scope: !12, file: !9, discriminator: 1)
!64 = !DILocation(line: 17, column: 1, scope: !12)
!65 = !DILocalVariable(name: "dest", arg: 1, scope: !15, file: !9, line: 19, type: !5)
!66 = !DILocation(line: 19, column: 22, scope: !15)
!67 = !DILocalVariable(name: "src", arg: 2, scope: !15, file: !9, line: 19, type: !5)
!68 = !DILocation(line: 19, column: 34, scope: !15)
!69 = !DILocalVariable(name: "len", arg: 3, scope: !15, file: !9, line: 19, type: !4)
!70 = !DILocation(line: 19, column: 43, scope: !15)
!71 = !DILocation(line: 21, column: 10, scope: !15)
!72 = !DILocation(line: 21, column: 16, scope: !15)
!73 = !DILocation(line: 21, column: 21, scope: !15)
!74 = !DILocation(line: 21, column: 2, scope: !15)
!75 = !DILocation(line: 22, column: 4, scope: !15)
!76 = !DILocation(line: 22, column: 11, scope: !15)
!77 = !DILocation(line: 22, column: 9, scope: !15)
!78 = !DILocation(line: 22, column: 16, scope: !15)
!79 = !DILocation(line: 23, column: 1, scope: !15)
!80 = !DILocalVariable(name: "str", arg: 1, scope: !18, file: !9, line: 30, type: !5)
!81 = !DILocation(line: 30, column: 19, scope: !18)
!82 = !DILocalVariable(name: "what", arg: 2, scope: !18, file: !9, line: 30, type: !5)
!83 = !DILocation(line: 30, column: 30, scope: !18)
!84 = !DILocalVariable(name: "by", arg: 3, scope: !18, file: !9, line: 30, type: !5)
!85 = !DILocation(line: 30, column: 42, scope: !18)
!86 = !DILocalVariable(name: "max_length", arg: 4, scope: !18, file: !9, line: 30, type: !4)
!87 = !DILocation(line: 30, column: 50, scope: !18)
!88 = !DILocalVariable(name: "foo", scope: !18, file: !9, line: 32, type: !5)
!89 = !DILocation(line: 32, column: 8, scope: !18)
!90 = !DILocalVariable(name: "bar", scope: !18, file: !9, line: 32, type: !5)
!91 = !DILocation(line: 32, column: 14, scope: !18)
!92 = !DILocation(line: 32, column: 20, scope: !18)
!93 = !DILocalVariable(name: "i", scope: !18, file: !9, line: 33, type: !4)
!94 = !DILocation(line: 33, column: 13, scope: !18)
!95 = !DILocalVariable(name: "str_length", scope: !18, file: !9, line: 34, type: !4)
!96 = !DILocation(line: 34, column: 13, scope: !18)
!97 = !DILocalVariable(name: "what_length", scope: !18, file: !9, line: 34, type: !4)
!98 = !DILocation(line: 34, column: 25, scope: !18)
!99 = !DILocalVariable(name: "by_length", scope: !18, file: !9, line: 34, type: !4)
!100 = !DILocation(line: 34, column: 38, scope: !18)
!101 = !DILocation(line: 37, column: 15, scope: !102)
!102 = distinct !DILexicalBlock(scope: !18, file: !9, line: 37, column: 13)
!103 = !DILocation(line: 37, column: 13, scope: !18)
!104 = !DILocation(line: 37, column: 20, scope: !105)
!105 = !DILexicalBlockFile(scope: !102, file: !9, discriminator: 1)
!106 = !DILocation(line: 38, column: 15, scope: !107)
!107 = distinct !DILexicalBlock(scope: !18, file: !9, line: 38, column: 13)
!108 = !DILocation(line: 38, column: 13, scope: !18)
!109 = !DILocation(line: 38, column: 21, scope: !110)
!110 = !DILexicalBlockFile(scope: !107, file: !9, discriminator: 1)
!111 = !DILocation(line: 39, column: 15, scope: !112)
!112 = distinct !DILexicalBlock(scope: !18, file: !9, line: 39, column: 13)
!113 = !DILocation(line: 39, column: 13, scope: !18)
!114 = !DILocation(line: 39, column: 19, scope: !115)
!115 = !DILexicalBlockFile(scope: !112, file: !9, discriminator: 1)
!116 = !DILocation(line: 41, column: 30, scope: !18)
!117 = !DILocation(line: 41, column: 23, scope: !18)
!118 = !DILocation(line: 41, column: 21, scope: !18)
!119 = !DILocation(line: 42, column: 28, scope: !18)
!120 = !DILocation(line: 42, column: 21, scope: !18)
!121 = !DILocation(line: 42, column: 19, scope: !18)
!122 = !DILocation(line: 43, column: 29, scope: !18)
!123 = !DILocation(line: 43, column: 22, scope: !18)
!124 = !DILocation(line: 43, column: 20, scope: !18)
!125 = !DILocation(line: 45, column: 22, scope: !18)
!126 = !DILocation(line: 45, column: 27, scope: !18)
!127 = !DILocation(line: 45, column: 15, scope: !18)
!128 = !DILocation(line: 45, column: 13, scope: !18)
!129 = !DILocation(line: 49, column: 2, scope: !18)
!130 = !DILocation(line: 49, column: 11, scope: !131)
!131 = !DILexicalBlockFile(scope: !18, file: !9, discriminator: 1)
!132 = !DILocation(line: 49, column: 10, scope: !131)
!133 = !DILocation(line: 49, column: 16, scope: !131)
!134 = !DILocation(line: 50, column: 20, scope: !18)
!135 = !DILocation(line: 50, column: 33, scope: !18)
!136 = !DILocation(line: 50, column: 31, scope: !18)
!137 = !DILocation(line: 50, column: 45, scope: !18)
!138 = !DILocation(line: 50, column: 43, scope: !18)
!139 = !DILocation(line: 50, column: 61, scope: !18)
!140 = !DILocation(line: 50, column: 72, scope: !18)
!141 = !DILocation(line: 50, column: 58, scope: !18)
!142 = !DILocation(line: 49, column: 2, scope: !143)
!143 = !DILexicalBlockFile(scope: !18, file: !9, discriminator: 2)
!144 = !DILocation(line: 52, column: 19, scope: !145)
!145 = distinct !DILexicalBlock(scope: !18, file: !9, line: 51, column: 9)
!146 = !DILocation(line: 52, column: 32, scope: !145)
!147 = !DILocation(line: 52, column: 25, scope: !145)
!148 = !DILocation(line: 52, column: 23, scope: !145)
!149 = !DILocation(line: 52, column: 17, scope: !145)
!150 = !DILocation(line: 53, column: 21, scope: !145)
!151 = !DILocation(line: 53, column: 26, scope: !145)
!152 = !DILocation(line: 53, column: 39, scope: !145)
!153 = !DILocation(line: 53, column: 32, scope: !145)
!154 = !DILocation(line: 53, column: 30, scope: !145)
!155 = !DILocation(line: 53, column: 53, scope: !145)
!156 = !DILocation(line: 53, column: 66, scope: !145)
!157 = !DILocation(line: 53, column: 59, scope: !158)
!158 = !DILexicalBlockFile(scope: !145, file: !9, discriminator: 1)
!159 = !DILocation(line: 53, column: 57, scope: !145)
!160 = !DILocation(line: 53, column: 46, scope: !161)
!161 = !DILexicalBlockFile(scope: !145, file: !9, discriminator: 2)
!162 = !DILocation(line: 53, column: 73, scope: !145)
!163 = !DILocation(line: 53, column: 13, scope: !164)
!164 = !DILexicalBlockFile(scope: !145, file: !9, discriminator: 3)
!165 = !DILocation(line: 54, column: 13, scope: !145)
!166 = !DILocation(line: 54, column: 18, scope: !145)
!167 = !DILocation(line: 54, column: 29, scope: !145)
!168 = !DILocation(line: 54, column: 22, scope: !145)
!169 = !DILocation(line: 54, column: 6, scope: !158)
!170 = !DILocation(line: 55, column: 14, scope: !145)
!171 = !DILocation(line: 56, column: 26, scope: !145)
!172 = !DILocation(line: 56, column: 31, scope: !145)
!173 = !DILocation(line: 56, column: 19, scope: !145)
!174 = !DILocation(line: 56, column: 17, scope: !145)
!175 = !DILocation(line: 57, column: 33, scope: !145)
!176 = !DILocation(line: 57, column: 26, scope: !145)
!177 = !DILocation(line: 57, column: 24, scope: !145)
!178 = !DILocation(line: 49, column: 2, scope: !179)
!179 = !DILexicalBlockFile(scope: !18, file: !9, discriminator: 3)
!180 = !DILocation(line: 59, column: 12, scope: !18)
!181 = !DILocation(line: 59, column: 5, scope: !18)
!182 = !DILocation(line: 60, column: 1, scope: !18)
!183 = !DILocalVariable(name: "list", arg: 1, scope: !21, file: !9, line: 67, type: !5)
!184 = !DILocation(line: 67, column: 25, scope: !21)
!185 = !DILocalVariable(name: "n", arg: 2, scope: !21, file: !9, line: 67, type: !4)
!186 = !DILocation(line: 67, column: 35, scope: !21)
!187 = !DILocalVariable(name: "str", scope: !21, file: !9, line: 69, type: !5)
!188 = !DILocation(line: 69, column: 11, scope: !21)
!189 = !DILocalVariable(name: "tok", scope: !21, file: !9, line: 69, type: !5)
!190 = !DILocation(line: 69, column: 17, scope: !21)
!191 = !DILocalVariable(name: "count", scope: !21, file: !9, line: 70, type: !4)
!192 = !DILocation(line: 70, column: 9, scope: !21)
!193 = !DILocalVariable(name: "firstrun", scope: !21, file: !9, line: 70, type: !4)
!194 = !DILocation(line: 70, column: 21, scope: !21)
!195 = !DILocation(line: 72, column: 50, scope: !21)
!196 = !DILocation(line: 72, column: 43, scope: !21)
!197 = !DILocation(line: 72, column: 56, scope: !21)
!198 = !DILocation(line: 72, column: 40, scope: !21)
!199 = !DILocation(line: 72, column: 20, scope: !200)
!200 = !DILexicalBlockFile(scope: !21, file: !9, discriminator: 1)
!201 = !DILocation(line: 72, column: 9, scope: !21)
!202 = !DILocation(line: 73, column: 10, scope: !203)
!203 = distinct !DILexicalBlock(scope: !21, file: !9, line: 73, column: 9)
!204 = !DILocation(line: 73, column: 9, scope: !21)
!205 = !DILocation(line: 74, column: 9, scope: !203)
!206 = !DILocation(line: 76, column: 12, scope: !21)
!207 = !DILocation(line: 76, column: 27, scope: !21)
!208 = !DILocation(line: 76, column: 20, scope: !21)
!209 = !DILocation(line: 76, column: 33, scope: !21)
!210 = !DILocation(line: 76, column: 5, scope: !200)
!211 = !DILocation(line: 77, column: 13, scope: !21)
!212 = !DILocation(line: 77, column: 18, scope: !21)
!213 = !DILocation(line: 77, column: 31, scope: !21)
!214 = !DILocation(line: 77, column: 24, scope: !21)
!215 = !DILocation(line: 77, column: 5, scope: !200)
!216 = !DILocation(line: 80, column: 13, scope: !21)
!217 = !DILocation(line: 80, column: 6, scope: !21)
!218 = !DILocation(line: 80, column: 2, scope: !21)
!219 = !DILocation(line: 80, column: 20, scope: !21)
!220 = !DILocation(line: 82, column: 5, scope: !21)
!221 = !DILocation(line: 83, column: 13, scope: !222)
!222 = distinct !DILexicalBlock(scope: !223, file: !9, line: 83, column: 13)
!223 = distinct !DILexicalBlock(scope: !224, file: !9, line: 82, column: 14)
!224 = distinct !DILexicalBlock(scope: !225, file: !9, line: 82, column: 5)
!225 = distinct !DILexicalBlock(scope: !21, file: !9, line: 82, column: 5)
!226 = !DILocation(line: 83, column: 13, scope: !223)
!227 = !DILocation(line: 84, column: 26, scope: !222)
!228 = !DILocation(line: 84, column: 19, scope: !222)
!229 = !DILocation(line: 84, column: 17, scope: !222)
!230 = !DILocation(line: 84, column: 13, scope: !222)
!231 = !DILocation(line: 86, column: 19, scope: !222)
!232 = !DILocation(line: 86, column: 17, scope: !222)
!233 = !DILocation(line: 88, column: 14, scope: !234)
!234 = distinct !DILexicalBlock(scope: !223, file: !9, line: 88, column: 13)
!235 = !DILocation(line: 88, column: 18, scope: !234)
!236 = !DILocation(line: 88, column: 22, scope: !237)
!237 = !DILexicalBlockFile(scope: !234, file: !9, discriminator: 1)
!238 = !DILocation(line: 88, column: 21, scope: !237)
!239 = !DILocation(line: 88, column: 26, scope: !237)
!240 = !DILocation(line: 88, column: 13, scope: !237)
!241 = !DILocation(line: 89, column: 9, scope: !242)
!242 = distinct !DILexicalBlock(scope: !234, file: !9, line: 88, column: 35)
!243 = !DILocation(line: 89, column: 4, scope: !242)
!244 = !DILocation(line: 90, column: 13, scope: !242)
!245 = !DILocation(line: 93, column: 20, scope: !246)
!246 = distinct !DILexicalBlock(scope: !223, file: !9, line: 93, column: 13)
!247 = !DILocation(line: 93, column: 13, scope: !246)
!248 = !DILocation(line: 93, column: 13, scope: !223)
!249 = !DILocalVariable(name: "start", scope: !250, file: !9, line: 94, type: !5)
!250 = distinct !DILexicalBlock(scope: !246, file: !9, line: 93, column: 31)
!251 = !DILocation(line: 94, column: 19, scope: !250)
!252 = !DILocalVariable(name: "end", scope: !250, file: !9, line: 94, type: !5)
!253 = !DILocation(line: 94, column: 27, scope: !250)
!254 = !DILocalVariable(name: "s", scope: !250, file: !9, line: 95, type: !4)
!255 = !DILocation(line: 95, column: 17, scope: !250)
!256 = !DILocalVariable(name: "e", scope: !250, file: !9, line: 95, type: !4)
!257 = !DILocation(line: 95, column: 20, scope: !250)
!258 = !DILocation(line: 96, column: 21, scope: !250)
!259 = !DILocation(line: 96, column: 19, scope: !250)
!260 = !DILocation(line: 97, column: 26, scope: !250)
!261 = !DILocation(line: 97, column: 19, scope: !250)
!262 = !DILocation(line: 97, column: 17, scope: !250)
!263 = !DILocation(line: 98, column: 14, scope: !250)
!264 = !DILocation(line: 98, column: 18, scope: !250)
!265 = !DILocation(line: 99, column: 16, scope: !250)
!266 = !DILocation(line: 100, column: 19, scope: !267)
!267 = distinct !DILexicalBlock(scope: !250, file: !9, line: 100, column: 17)
!268 = !DILocation(line: 100, column: 18, scope: !267)
!269 = !DILocation(line: 100, column: 25, scope: !267)
!270 = !DILocation(line: 100, column: 30, scope: !271)
!271 = !DILexicalBlockFile(scope: !267, file: !9, discriminator: 1)
!272 = !DILocation(line: 100, column: 29, scope: !271)
!273 = !DILocation(line: 100, column: 17, scope: !271)
!274 = !DILocation(line: 101, column: 10, scope: !275)
!275 = distinct !DILexicalBlock(scope: !267, file: !9, line: 100, column: 35)
!276 = !DILocation(line: 101, column: 5, scope: !275)
!277 = !DILocation(line: 102, column: 17, scope: !275)
!278 = !DILocation(line: 104, column: 22, scope: !250)
!279 = !DILocation(line: 104, column: 17, scope: !250)
!280 = !DILocation(line: 104, column: 15, scope: !250)
!281 = !DILocation(line: 105, column: 22, scope: !250)
!282 = !DILocation(line: 105, column: 17, scope: !250)
!283 = !DILocation(line: 105, column: 15, scope: !250)
!284 = !DILocation(line: 106, column: 17, scope: !285)
!285 = distinct !DILexicalBlock(scope: !250, file: !9, line: 106, column: 17)
!286 = !DILocation(line: 106, column: 19, scope: !285)
!287 = !DILocation(line: 106, column: 23, scope: !285)
!288 = !DILocation(line: 106, column: 26, scope: !289)
!289 = !DILexicalBlockFile(scope: !285, file: !9, discriminator: 1)
!290 = !DILocation(line: 106, column: 28, scope: !289)
!291 = !DILocation(line: 106, column: 32, scope: !289)
!292 = !DILocation(line: 106, column: 35, scope: !293)
!293 = !DILexicalBlockFile(scope: !285, file: !9, discriminator: 2)
!294 = !DILocation(line: 106, column: 39, scope: !293)
!295 = !DILocation(line: 106, column: 37, scope: !293)
!296 = !DILocation(line: 106, column: 17, scope: !293)
!297 = !DILocation(line: 107, column: 10, scope: !298)
!298 = distinct !DILexicalBlock(scope: !285, file: !9, line: 106, column: 42)
!299 = !DILocation(line: 107, column: 5, scope: !298)
!300 = !DILocation(line: 108, column: 17, scope: !298)
!301 = !DILocation(line: 110, column: 22, scope: !250)
!302 = !DILocation(line: 110, column: 26, scope: !250)
!303 = !DILocation(line: 110, column: 24, scope: !250)
!304 = !DILocation(line: 110, column: 28, scope: !250)
!305 = !DILocation(line: 110, column: 19, scope: !250)
!306 = !DILocation(line: 111, column: 17, scope: !307)
!307 = distinct !DILexicalBlock(scope: !250, file: !9, line: 111, column: 17)
!308 = !DILocation(line: 111, column: 26, scope: !307)
!309 = !DILocation(line: 111, column: 23, scope: !307)
!310 = !DILocation(line: 111, column: 17, scope: !250)
!311 = !DILocation(line: 112, column: 10, scope: !312)
!312 = distinct !DILexicalBlock(scope: !307, file: !9, line: 111, column: 29)
!313 = !DILocation(line: 112, column: 5, scope: !312)
!314 = !DILocation(line: 113, column: 25, scope: !312)
!315 = !DILocation(line: 113, column: 30, scope: !312)
!316 = !DILocation(line: 113, column: 38, scope: !312)
!317 = !DILocation(line: 113, column: 36, scope: !312)
!318 = !DILocation(line: 113, column: 27, scope: !312)
!319 = !DILocation(line: 113, column: 17, scope: !312)
!320 = !DILocation(line: 115, column: 9, scope: !250)
!321 = !DILocation(line: 116, column: 18, scope: !322)
!322 = distinct !DILexicalBlock(scope: !246, file: !9, line: 115, column: 16)
!323 = !DILocation(line: 117, column: 17, scope: !324)
!324 = distinct !DILexicalBlock(scope: !322, file: !9, line: 117, column: 17)
!325 = !DILocation(line: 117, column: 26, scope: !324)
!326 = !DILocation(line: 117, column: 23, scope: !324)
!327 = !DILocation(line: 117, column: 17, scope: !322)
!328 = !DILocalVariable(name: "val", scope: !329, file: !9, line: 118, type: !4)
!329 = distinct !DILexicalBlock(scope: !324, file: !9, line: 117, column: 29)
!330 = !DILocation(line: 118, column: 9, scope: !329)
!331 = !DILocation(line: 118, column: 20, scope: !329)
!332 = !DILocation(line: 118, column: 15, scope: !329)
!333 = !DILocation(line: 119, column: 10, scope: !329)
!334 = !DILocation(line: 119, column: 5, scope: !329)
!335 = !DILocation(line: 120, column: 24, scope: !329)
!336 = !DILocation(line: 120, column: 17, scope: !329)
!337 = !DILocation(line: 123, column: 18, scope: !223)
!338 = !DILocation(line: 82, column: 5, scope: !339)
!339 = !DILexicalBlockFile(scope: !224, file: !9, discriminator: 1)
!340 = !DILocation(line: 125, column: 1, scope: !21)
