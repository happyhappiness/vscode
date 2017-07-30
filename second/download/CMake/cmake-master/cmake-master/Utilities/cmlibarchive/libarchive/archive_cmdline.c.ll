; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_cmdline.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_cmdline = type { i8*, i8**, i32 }
%struct.archive_string = type { i8*, i64, i64 }

; Function Attrs: nounwind uwtable
define i32 @__archive_cmdline_parse(%struct.archive_cmdline* %data, i8* %cmd) #0 !dbg !22 {
entry:
  %data.addr = alloca %struct.archive_cmdline*, align 8
  %cmd.addr = alloca i8*, align 8
  %as = alloca %struct.archive_string, align 8
  %p = alloca i8*, align 8
  %al = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive_cmdline* %data, %struct.archive_cmdline** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_cmdline** %data.addr, metadata !52, metadata !53), !dbg !54
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !55, metadata !53), !dbg !56
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !57, metadata !53), !dbg !58
  call void @llvm.dbg.declare(metadata i8** %p, metadata !59, metadata !53), !dbg !60
  call void @llvm.dbg.declare(metadata i64* %al, metadata !61, metadata !53), !dbg !62
  call void @llvm.dbg.declare(metadata i32* %r, metadata !63, metadata !53), !dbg !64
  br label %do.body, !dbg !65

do.body:                                          ; preds = %entry
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !66
  store i8* null, i8** %s, align 8, !dbg !66
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !66
  store i64 0, i64* %length, align 8, !dbg !66
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !66
  store i64 0, i64* %buffer_length, align 8, !dbg !66
  br label %do.end, !dbg !66

do.end:                                           ; preds = %do.body
  %0 = load i8*, i8** %cmd.addr, align 8, !dbg !69
  %call = call i64 @get_argument(%struct.archive_string* %as, i8* %0), !dbg !70
  store i64 %call, i64* %al, align 8, !dbg !71
  %1 = load i64, i64* %al, align 8, !dbg !72
  %cmp = icmp slt i64 %1, 0, !dbg !74
  br i1 %cmp, label %if.then, label %if.end, !dbg !75

if.then:                                          ; preds = %do.end
  store i32 -25, i32* %r, align 4, !dbg !76
  br label %exit_function, !dbg !78

if.end:                                           ; preds = %do.end
  %length1 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !79
  %2 = load i64, i64* %length1, align 8, !dbg !79
  %cmp2 = icmp eq i64 %2, 0, !dbg !81
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !82

if.then3:                                         ; preds = %if.end
  store i32 -25, i32* %r, align 4, !dbg !83
  br label %exit_function, !dbg !85

if.end4:                                          ; preds = %if.end
  %3 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !86
  %s5 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !87
  %4 = load i8*, i8** %s5, align 8, !dbg !87
  %call6 = call i32 @cmdline_set_path(%struct.archive_cmdline* %3, i8* %4), !dbg !88
  store i32 %call6, i32* %r, align 4, !dbg !89
  %5 = load i32, i32* %r, align 4, !dbg !90
  %cmp7 = icmp ne i32 %5, 0, !dbg !92
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !93

if.then8:                                         ; preds = %if.end4
  br label %exit_function, !dbg !94

if.end9:                                          ; preds = %if.end4
  %s10 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !95
  %6 = load i8*, i8** %s10, align 8, !dbg !95
  %call11 = call i8* @strrchr(i8* %6, i32 47) #5, !dbg !96
  store i8* %call11, i8** %p, align 8, !dbg !97
  %7 = load i8*, i8** %p, align 8, !dbg !98
  %cmp12 = icmp eq i8* %7, null, !dbg !100
  br i1 %cmp12, label %if.then13, label %if.else, !dbg !101

if.then13:                                        ; preds = %if.end9
  %s14 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !102
  %8 = load i8*, i8** %s14, align 8, !dbg !102
  store i8* %8, i8** %p, align 8, !dbg !103
  br label %if.end15, !dbg !104

if.else:                                          ; preds = %if.end9
  %9 = load i8*, i8** %p, align 8, !dbg !105
  %incdec.ptr = getelementptr inbounds i8, i8* %9, i32 1, !dbg !105
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !105
  br label %if.end15

if.end15:                                         ; preds = %if.else, %if.then13
  %10 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !106
  %11 = load i8*, i8** %p, align 8, !dbg !107
  %call16 = call i32 @cmdline_add_arg(%struct.archive_cmdline* %10, i8* %11), !dbg !108
  store i32 %call16, i32* %r, align 4, !dbg !109
  %12 = load i32, i32* %r, align 4, !dbg !110
  %cmp17 = icmp ne i32 %12, 0, !dbg !112
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !113

if.then18:                                        ; preds = %if.end15
  br label %exit_function, !dbg !114

if.end19:                                         ; preds = %if.end15
  %13 = load i64, i64* %al, align 8, !dbg !115
  %14 = load i8*, i8** %cmd.addr, align 8, !dbg !116
  %add.ptr = getelementptr inbounds i8, i8* %14, i64 %13, !dbg !116
  store i8* %add.ptr, i8** %cmd.addr, align 8, !dbg !116
  br label %for.cond, !dbg !117

for.cond:                                         ; preds = %if.end39, %if.end19
  %15 = load i8*, i8** %cmd.addr, align 8, !dbg !118
  %call20 = call i64 @get_argument(%struct.archive_string* %as, i8* %15), !dbg !122
  store i64 %call20, i64* %al, align 8, !dbg !123
  %16 = load i64, i64* %al, align 8, !dbg !124
  %cmp21 = icmp slt i64 %16, 0, !dbg !126
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !127

if.then22:                                        ; preds = %for.cond
  store i32 -25, i32* %r, align 4, !dbg !128
  br label %exit_function, !dbg !130

if.end23:                                         ; preds = %for.cond
  %17 = load i64, i64* %al, align 8, !dbg !131
  %cmp24 = icmp eq i64 %17, 0, !dbg !133
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !134

if.then25:                                        ; preds = %if.end23
  br label %for.end, !dbg !135

if.end26:                                         ; preds = %if.end23
  %18 = load i64, i64* %al, align 8, !dbg !136
  %19 = load i8*, i8** %cmd.addr, align 8, !dbg !137
  %add.ptr27 = getelementptr inbounds i8, i8* %19, i64 %18, !dbg !137
  store i8* %add.ptr27, i8** %cmd.addr, align 8, !dbg !137
  %length28 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !138
  %20 = load i64, i64* %length28, align 8, !dbg !138
  %cmp29 = icmp eq i64 %20, 0, !dbg !140
  br i1 %cmp29, label %land.lhs.true, label %if.end33, !dbg !141

land.lhs.true:                                    ; preds = %if.end26
  %21 = load i8*, i8** %cmd.addr, align 8, !dbg !142
  %22 = load i8, i8* %21, align 1, !dbg !144
  %conv = sext i8 %22 to i32, !dbg !144
  %cmp30 = icmp eq i32 %conv, 0, !dbg !145
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !146

if.then32:                                        ; preds = %land.lhs.true
  br label %for.end, !dbg !147

if.end33:                                         ; preds = %land.lhs.true, %if.end26
  %23 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !148
  %s34 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !149
  %24 = load i8*, i8** %s34, align 8, !dbg !149
  %call35 = call i32 @cmdline_add_arg(%struct.archive_cmdline* %23, i8* %24), !dbg !150
  store i32 %call35, i32* %r, align 4, !dbg !151
  %25 = load i32, i32* %r, align 4, !dbg !152
  %cmp36 = icmp ne i32 %25, 0, !dbg !154
  br i1 %cmp36, label %if.then38, label %if.end39, !dbg !155

if.then38:                                        ; preds = %if.end33
  br label %exit_function, !dbg !156

if.end39:                                         ; preds = %if.end33
  br label %for.cond, !dbg !157

for.end:                                          ; preds = %if.then32, %if.then25
  store i32 0, i32* %r, align 4, !dbg !159
  br label %exit_function, !dbg !160

exit_function:                                    ; preds = %for.end, %if.then38, %if.then22, %if.then18, %if.then8, %if.then3, %if.then
  call void @archive_string_free(%struct.archive_string* %as), !dbg !161
  %26 = load i32, i32* %r, align 4, !dbg !162
  ret i32 %26, !dbg !163
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i64 @get_argument(%struct.archive_string* %as, i8* %p) #0 !dbg !33 {
entry:
  %retval = alloca i64, align 8
  %as.addr = alloca %struct.archive_string*, align 8
  %p.addr = alloca i8*, align 8
  %s = alloca i8*, align 8
  %q = alloca i64, align 8
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !164, metadata !53), !dbg !165
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !166, metadata !53), !dbg !167
  call void @llvm.dbg.declare(metadata i8** %s, metadata !168, metadata !53), !dbg !169
  %0 = load i8*, i8** %p.addr, align 8, !dbg !170
  store i8* %0, i8** %s, align 8, !dbg !169
  %1 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !171
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %1, i32 0, i32 1, !dbg !171
  store i64 0, i64* %length, align 8, !dbg !171
  br label %while.cond, !dbg !172

while.cond:                                       ; preds = %while.body, %entry
  %2 = load i8*, i8** %s, align 8, !dbg !173
  %3 = load i8, i8* %2, align 1, !dbg !175
  %conv = sext i8 %3 to i32, !dbg !175
  %cmp = icmp ne i32 %conv, 0, !dbg !176
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !177

land.rhs:                                         ; preds = %while.cond
  %4 = load i8*, i8** %s, align 8, !dbg !178
  %5 = load i8, i8* %4, align 1, !dbg !180
  %conv2 = sext i8 %5 to i32, !dbg !180
  %cmp3 = icmp eq i32 %conv2, 32, !dbg !181
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %6 = phi i1 [ false, %while.cond ], [ %cmp3, %land.rhs ]
  br i1 %6, label %while.body, label %while.end, !dbg !182

while.body:                                       ; preds = %land.end
  %7 = load i8*, i8** %s, align 8, !dbg !184
  %incdec.ptr = getelementptr inbounds i8, i8* %7, i32 1, !dbg !184
  store i8* %incdec.ptr, i8** %s, align 8, !dbg !184
  br label %while.cond, !dbg !185

while.end:                                        ; preds = %land.end
  br label %while.cond5, !dbg !187

while.cond5:                                      ; preds = %if.end40, %while.end
  %8 = load i8*, i8** %s, align 8, !dbg !188
  %9 = load i8, i8* %8, align 1, !dbg !189
  %conv6 = sext i8 %9 to i32, !dbg !189
  %cmp7 = icmp ne i32 %conv6, 0, !dbg !190
  br i1 %cmp7, label %land.rhs9, label %land.end13, !dbg !191

land.rhs9:                                        ; preds = %while.cond5
  %10 = load i8*, i8** %s, align 8, !dbg !192
  %11 = load i8, i8* %10, align 1, !dbg !193
  %conv10 = sext i8 %11 to i32, !dbg !193
  %cmp11 = icmp ne i32 %conv10, 32, !dbg !194
  br label %land.end13

land.end13:                                       ; preds = %land.rhs9, %while.cond5
  %12 = phi i1 [ false, %while.cond5 ], [ %cmp11, %land.rhs9 ]
  br i1 %12, label %while.body14, label %while.end41, !dbg !195

while.body14:                                     ; preds = %land.end13
  %13 = load i8*, i8** %s, align 8, !dbg !196
  %14 = load i8, i8* %13, align 1, !dbg !199
  %conv15 = sext i8 %14 to i32, !dbg !199
  %cmp16 = icmp eq i32 %conv15, 92, !dbg !200
  br i1 %cmp16, label %if.then, label %if.else24, !dbg !201

if.then:                                          ; preds = %while.body14
  %15 = load i8*, i8** %s, align 8, !dbg !202
  %arrayidx = getelementptr inbounds i8, i8* %15, i64 1, !dbg !202
  %16 = load i8, i8* %arrayidx, align 1, !dbg !202
  %conv18 = sext i8 %16 to i32, !dbg !202
  %cmp19 = icmp ne i32 %conv18, 0, !dbg !205
  br i1 %cmp19, label %if.then21, label %if.else, !dbg !206

if.then21:                                        ; preds = %if.then
  %17 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !207
  %18 = load i8*, i8** %s, align 8, !dbg !209
  %arrayidx22 = getelementptr inbounds i8, i8* %18, i64 1, !dbg !209
  %19 = load i8, i8* %arrayidx22, align 1, !dbg !209
  %call = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %17, i8 signext %19), !dbg !210
  %20 = load i8*, i8** %s, align 8, !dbg !211
  %add.ptr = getelementptr inbounds i8, i8* %20, i64 2, !dbg !211
  store i8* %add.ptr, i8** %s, align 8, !dbg !211
  br label %if.end, !dbg !212

if.else:                                          ; preds = %if.then
  %21 = load i8*, i8** %s, align 8, !dbg !213
  %incdec.ptr23 = getelementptr inbounds i8, i8* %21, i32 1, !dbg !213
  store i8* %incdec.ptr23, i8** %s, align 8, !dbg !213
  br label %while.end41, !dbg !215

if.end:                                           ; preds = %if.then21
  br label %if.end40, !dbg !216

if.else24:                                        ; preds = %while.body14
  %22 = load i8*, i8** %s, align 8, !dbg !217
  %23 = load i8, i8* %22, align 1, !dbg !220
  %conv25 = sext i8 %23 to i32, !dbg !220
  %cmp26 = icmp eq i32 %conv25, 34, !dbg !221
  br i1 %cmp26, label %if.then28, label %if.else35, !dbg !220

if.then28:                                        ; preds = %if.else24
  call void @llvm.dbg.declare(metadata i64* %q, metadata !222, metadata !53), !dbg !224
  %24 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !225
  %25 = load i8*, i8** %s, align 8, !dbg !226
  %call29 = call i64 @extract_quotation(%struct.archive_string* %24, i8* %25), !dbg !227
  store i64 %call29, i64* %q, align 8, !dbg !224
  %26 = load i64, i64* %q, align 8, !dbg !228
  %cmp30 = icmp slt i64 %26, 0, !dbg !230
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !231

if.then32:                                        ; preds = %if.then28
  store i64 -25, i64* %retval, align 8, !dbg !232
  br label %return, !dbg !232

if.end33:                                         ; preds = %if.then28
  %27 = load i64, i64* %q, align 8, !dbg !233
  %28 = load i8*, i8** %s, align 8, !dbg !234
  %add.ptr34 = getelementptr inbounds i8, i8* %28, i64 %27, !dbg !234
  store i8* %add.ptr34, i8** %s, align 8, !dbg !234
  br label %if.end39, !dbg !235

if.else35:                                        ; preds = %if.else24
  %29 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !236
  %30 = load i8*, i8** %s, align 8, !dbg !238
  %arrayidx36 = getelementptr inbounds i8, i8* %30, i64 0, !dbg !238
  %31 = load i8, i8* %arrayidx36, align 1, !dbg !238
  %call37 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %29, i8 signext %31), !dbg !239
  %32 = load i8*, i8** %s, align 8, !dbg !240
  %incdec.ptr38 = getelementptr inbounds i8, i8* %32, i32 1, !dbg !240
  store i8* %incdec.ptr38, i8** %s, align 8, !dbg !240
  br label %if.end39

if.end39:                                         ; preds = %if.else35, %if.end33
  br label %if.end40

if.end40:                                         ; preds = %if.end39, %if.end
  br label %while.cond5, !dbg !241

while.end41:                                      ; preds = %if.else, %land.end13
  %33 = load i8*, i8** %s, align 8, !dbg !242
  %34 = load i8*, i8** %p.addr, align 8, !dbg !243
  %sub.ptr.lhs.cast = ptrtoint i8* %33 to i64, !dbg !244
  %sub.ptr.rhs.cast = ptrtoint i8* %34 to i64, !dbg !244
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !244
  store i64 %sub.ptr.sub, i64* %retval, align 8, !dbg !245
  br label %return, !dbg !245

return:                                           ; preds = %while.end41, %if.then32
  %35 = load i64, i64* %retval, align 8, !dbg !246
  ret i64 %35, !dbg !246
}

; Function Attrs: nounwind uwtable
define internal i32 @cmdline_set_path(%struct.archive_cmdline* %data, i8* %path) #0 !dbg !47 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.archive_cmdline*, align 8
  %path.addr = alloca i8*, align 8
  %newptr = alloca i8*, align 8
  store %struct.archive_cmdline* %data, %struct.archive_cmdline** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_cmdline** %data.addr, metadata !247, metadata !53), !dbg !248
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !249, metadata !53), !dbg !250
  call void @llvm.dbg.declare(metadata i8** %newptr, metadata !251, metadata !53), !dbg !252
  %0 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !253
  %path1 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %0, i32 0, i32 0, !dbg !254
  %1 = load i8*, i8** %path1, align 8, !dbg !254
  %2 = load i8*, i8** %path.addr, align 8, !dbg !255
  %call = call i64 @strlen(i8* %2) #5, !dbg !256
  %add = add i64 %call, 1, !dbg !257
  %call2 = call i8* @realloc(i8* %1, i64 %add) #6, !dbg !258
  store i8* %call2, i8** %newptr, align 8, !dbg !260
  %3 = load i8*, i8** %newptr, align 8, !dbg !261
  %cmp = icmp eq i8* %3, null, !dbg !263
  br i1 %cmp, label %if.then, label %if.end, !dbg !264

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !265
  br label %return, !dbg !265

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %newptr, align 8, !dbg !266
  %5 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !267
  %path3 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %5, i32 0, i32 0, !dbg !268
  store i8* %4, i8** %path3, align 8, !dbg !269
  %6 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !270
  %path4 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %6, i32 0, i32 0, !dbg !271
  %7 = load i8*, i8** %path4, align 8, !dbg !271
  %8 = load i8*, i8** %path.addr, align 8, !dbg !272
  %call5 = call i8* @strcpy(i8* %7, i8* %8) #6, !dbg !273
  store i32 0, i32* %retval, align 4, !dbg !274
  br label %return, !dbg !274

return:                                           ; preds = %if.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !275
  ret i32 %9, !dbg !275
}

; Function Attrs: nounwind readonly
declare i8* @strrchr(i8*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @cmdline_add_arg(%struct.archive_cmdline* %data, i8* %arg) #0 !dbg !48 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.archive_cmdline*, align 8
  %arg.addr = alloca i8*, align 8
  %newargv = alloca i8**, align 8
  store %struct.archive_cmdline* %data, %struct.archive_cmdline** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_cmdline** %data.addr, metadata !276, metadata !53), !dbg !277
  store i8* %arg, i8** %arg.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %arg.addr, metadata !278, metadata !53), !dbg !279
  call void @llvm.dbg.declare(metadata i8*** %newargv, metadata !280, metadata !53), !dbg !281
  %0 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !282
  %path = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %0, i32 0, i32 0, !dbg !284
  %1 = load i8*, i8** %path, align 8, !dbg !284
  %cmp = icmp eq i8* %1, null, !dbg !285
  br i1 %cmp, label %if.then, label %if.end, !dbg !286

if.then:                                          ; preds = %entry
  store i32 -25, i32* %retval, align 4, !dbg !287
  br label %return, !dbg !287

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !288
  %argv = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %2, i32 0, i32 1, !dbg !289
  %3 = load i8**, i8*** %argv, align 8, !dbg !289
  %4 = bitcast i8** %3 to i8*, !dbg !288
  %5 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !290
  %argc = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %5, i32 0, i32 2, !dbg !291
  %6 = load i32, i32* %argc, align 8, !dbg !291
  %add = add nsw i32 %6, 2, !dbg !292
  %conv = sext i32 %add to i64, !dbg !293
  %mul = mul i64 %conv, 8, !dbg !294
  %call = call i8* @realloc(i8* %4, i64 %mul) #6, !dbg !295
  %7 = bitcast i8* %call to i8**, !dbg !295
  store i8** %7, i8*** %newargv, align 8, !dbg !296
  %8 = load i8**, i8*** %newargv, align 8, !dbg !297
  %cmp1 = icmp eq i8** %8, null, !dbg !299
  br i1 %cmp1, label %if.then3, label %if.end4, !dbg !300

if.then3:                                         ; preds = %if.end
  store i32 -30, i32* %retval, align 4, !dbg !301
  br label %return, !dbg !301

if.end4:                                          ; preds = %if.end
  %9 = load i8**, i8*** %newargv, align 8, !dbg !302
  %10 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !303
  %argv5 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %10, i32 0, i32 1, !dbg !304
  store i8** %9, i8*** %argv5, align 8, !dbg !305
  %11 = load i8*, i8** %arg.addr, align 8, !dbg !306
  %call6 = call noalias i8* @strdup(i8* %11) #6, !dbg !307
  %12 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !308
  %argc7 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %12, i32 0, i32 2, !dbg !309
  %13 = load i32, i32* %argc7, align 8, !dbg !309
  %idxprom = sext i32 %13 to i64, !dbg !310
  %14 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !310
  %argv8 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %14, i32 0, i32 1, !dbg !311
  %15 = load i8**, i8*** %argv8, align 8, !dbg !311
  %arrayidx = getelementptr inbounds i8*, i8** %15, i64 %idxprom, !dbg !310
  store i8* %call6, i8** %arrayidx, align 8, !dbg !312
  %16 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !313
  %argc9 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %16, i32 0, i32 2, !dbg !315
  %17 = load i32, i32* %argc9, align 8, !dbg !315
  %idxprom10 = sext i32 %17 to i64, !dbg !316
  %18 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !316
  %argv11 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %18, i32 0, i32 1, !dbg !317
  %19 = load i8**, i8*** %argv11, align 8, !dbg !317
  %arrayidx12 = getelementptr inbounds i8*, i8** %19, i64 %idxprom10, !dbg !316
  %20 = load i8*, i8** %arrayidx12, align 8, !dbg !316
  %cmp13 = icmp eq i8* %20, null, !dbg !318
  br i1 %cmp13, label %if.then15, label %if.end16, !dbg !319

if.then15:                                        ; preds = %if.end4
  store i32 -30, i32* %retval, align 4, !dbg !320
  br label %return, !dbg !320

if.end16:                                         ; preds = %if.end4
  %21 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !321
  %argc17 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %21, i32 0, i32 2, !dbg !322
  %22 = load i32, i32* %argc17, align 8, !dbg !323
  %inc = add nsw i32 %22, 1, !dbg !323
  store i32 %inc, i32* %argc17, align 8, !dbg !323
  %idxprom18 = sext i32 %inc to i64, !dbg !324
  %23 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !324
  %argv19 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %23, i32 0, i32 1, !dbg !325
  %24 = load i8**, i8*** %argv19, align 8, !dbg !325
  %arrayidx20 = getelementptr inbounds i8*, i8** %24, i64 %idxprom18, !dbg !324
  store i8* null, i8** %arrayidx20, align 8, !dbg !326
  store i32 0, i32* %retval, align 4, !dbg !327
  br label %return, !dbg !327

return:                                           ; preds = %if.end16, %if.then15, %if.then3, %if.then
  %25 = load i32, i32* %retval, align 4, !dbg !328
  ret i32 %25, !dbg !328
}

declare void @archive_string_free(%struct.archive_string*) #3

; Function Attrs: nounwind uwtable
define %struct.archive_cmdline* @__archive_cmdline_allocate() #0 !dbg !27 {
entry:
  %call = call noalias i8* @calloc(i64 1, i64 24) #6, !dbg !329
  %0 = bitcast i8* %call to %struct.archive_cmdline*, !dbg !330
  ret %struct.archive_cmdline* %0, !dbg !331
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #4

; Function Attrs: nounwind uwtable
define i32 @__archive_cmdline_free(%struct.archive_cmdline* %data) #0 !dbg !30 {
entry:
  %data.addr = alloca %struct.archive_cmdline*, align 8
  %i = alloca i32, align 4
  store %struct.archive_cmdline* %data, %struct.archive_cmdline** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_cmdline** %data.addr, metadata !332, metadata !53), !dbg !333
  %0 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !334
  %tobool = icmp ne %struct.archive_cmdline* %0, null, !dbg !334
  br i1 %tobool, label %if.then, label %if.end8, !dbg !336

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !337
  %path = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %1, i32 0, i32 0, !dbg !339
  %2 = load i8*, i8** %path, align 8, !dbg !339
  call void @free(i8* %2) #6, !dbg !340
  %3 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !341
  %argv = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %3, i32 0, i32 1, !dbg !343
  %4 = load i8**, i8*** %argv, align 8, !dbg !343
  %cmp = icmp ne i8** %4, null, !dbg !344
  br i1 %cmp, label %if.then1, label %if.end, !dbg !345

if.then1:                                         ; preds = %if.then
  call void @llvm.dbg.declare(metadata i32* %i, metadata !346, metadata !53), !dbg !348
  store i32 0, i32* %i, align 4, !dbg !349
  br label %for.cond, !dbg !351

for.cond:                                         ; preds = %for.inc, %if.then1
  %5 = load i32, i32* %i, align 4, !dbg !352
  %idxprom = sext i32 %5 to i64, !dbg !355
  %6 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !355
  %argv2 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %6, i32 0, i32 1, !dbg !356
  %7 = load i8**, i8*** %argv2, align 8, !dbg !356
  %arrayidx = getelementptr inbounds i8*, i8** %7, i64 %idxprom, !dbg !355
  %8 = load i8*, i8** %arrayidx, align 8, !dbg !355
  %cmp3 = icmp ne i8* %8, null, !dbg !357
  br i1 %cmp3, label %for.body, label %for.end, !dbg !358

for.body:                                         ; preds = %for.cond
  %9 = load i32, i32* %i, align 4, !dbg !359
  %idxprom4 = sext i32 %9 to i64, !dbg !360
  %10 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !360
  %argv5 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %10, i32 0, i32 1, !dbg !361
  %11 = load i8**, i8*** %argv5, align 8, !dbg !361
  %arrayidx6 = getelementptr inbounds i8*, i8** %11, i64 %idxprom4, !dbg !360
  %12 = load i8*, i8** %arrayidx6, align 8, !dbg !360
  call void @free(i8* %12) #6, !dbg !362
  br label %for.inc, !dbg !362

for.inc:                                          ; preds = %for.body
  %13 = load i32, i32* %i, align 4, !dbg !363
  %inc = add nsw i32 %13, 1, !dbg !363
  store i32 %inc, i32* %i, align 4, !dbg !363
  br label %for.cond, !dbg !365

for.end:                                          ; preds = %for.cond
  %14 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !366
  %argv7 = getelementptr inbounds %struct.archive_cmdline, %struct.archive_cmdline* %14, i32 0, i32 1, !dbg !367
  %15 = load i8**, i8*** %argv7, align 8, !dbg !367
  %16 = bitcast i8** %15 to i8*, !dbg !366
  call void @free(i8* %16) #6, !dbg !368
  br label %if.end, !dbg !369

if.end:                                           ; preds = %for.end, %if.then
  %17 = load %struct.archive_cmdline*, %struct.archive_cmdline** %data.addr, align 8, !dbg !370
  %18 = bitcast %struct.archive_cmdline* %17 to i8*, !dbg !370
  call void @free(i8* %18) #6, !dbg !371
  br label %if.end8, !dbg !372

if.end8:                                          ; preds = %if.end, %entry
  ret i32 0, !dbg !373
}

; Function Attrs: nounwind
declare void @free(i8*) #4

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #3

; Function Attrs: nounwind uwtable
define internal i64 @extract_quotation(%struct.archive_string* %as, i8* %p) #0 !dbg !46 {
entry:
  %retval = alloca i64, align 8
  %as.addr = alloca %struct.archive_string*, align 8
  %p.addr = alloca i8*, align 8
  %s = alloca i8*, align 8
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !374, metadata !53), !dbg !375
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !376, metadata !53), !dbg !377
  call void @llvm.dbg.declare(metadata i8** %s, metadata !378, metadata !53), !dbg !379
  %0 = load i8*, i8** %p.addr, align 8, !dbg !380
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 1, !dbg !382
  store i8* %add.ptr, i8** %s, align 8, !dbg !383
  br label %for.cond, !dbg !384

for.cond:                                         ; preds = %if.end18, %entry
  %1 = load i8*, i8** %s, align 8, !dbg !385
  %2 = load i8, i8* %1, align 1, !dbg !388
  %tobool = icmp ne i8 %2, 0, !dbg !389
  br i1 %tobool, label %for.body, label %for.end, !dbg !389

for.body:                                         ; preds = %for.cond
  %3 = load i8*, i8** %s, align 8, !dbg !390
  %4 = load i8, i8* %3, align 1, !dbg !393
  %conv = sext i8 %4 to i32, !dbg !393
  %cmp = icmp eq i32 %conv, 92, !dbg !394
  br i1 %cmp, label %if.then, label %if.else8, !dbg !395

if.then:                                          ; preds = %for.body
  %5 = load i8*, i8** %s, align 8, !dbg !396
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 1, !dbg !396
  %6 = load i8, i8* %arrayidx, align 1, !dbg !396
  %conv2 = sext i8 %6 to i32, !dbg !396
  %cmp3 = icmp ne i32 %conv2, 0, !dbg !399
  br i1 %cmp3, label %if.then5, label %if.else, !dbg !400

if.then5:                                         ; preds = %if.then
  %7 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !401
  %8 = load i8*, i8** %s, align 8, !dbg !403
  %arrayidx6 = getelementptr inbounds i8, i8* %8, i64 1, !dbg !403
  %9 = load i8, i8* %arrayidx6, align 1, !dbg !403
  %call = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %7, i8 signext %9), !dbg !404
  %10 = load i8*, i8** %s, align 8, !dbg !405
  %add.ptr7 = getelementptr inbounds i8, i8* %10, i64 2, !dbg !405
  store i8* %add.ptr7, i8** %s, align 8, !dbg !405
  br label %if.end, !dbg !406

if.else:                                          ; preds = %if.then
  %11 = load i8*, i8** %s, align 8, !dbg !407
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !407
  store i8* %incdec.ptr, i8** %s, align 8, !dbg !407
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then5
  br label %if.end18, !dbg !408

if.else8:                                         ; preds = %for.body
  %12 = load i8*, i8** %s, align 8, !dbg !409
  %13 = load i8, i8* %12, align 1, !dbg !412
  %conv9 = sext i8 %13 to i32, !dbg !412
  %cmp10 = icmp eq i32 %conv9, 34, !dbg !413
  br i1 %cmp10, label %if.then12, label %if.else13, !dbg !412

if.then12:                                        ; preds = %if.else8
  br label %for.end, !dbg !414

if.else13:                                        ; preds = %if.else8
  %14 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !415
  %15 = load i8*, i8** %s, align 8, !dbg !417
  %arrayidx14 = getelementptr inbounds i8, i8* %15, i64 0, !dbg !417
  %16 = load i8, i8* %arrayidx14, align 1, !dbg !417
  %call15 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %14, i8 signext %16), !dbg !418
  %17 = load i8*, i8** %s, align 8, !dbg !419
  %incdec.ptr16 = getelementptr inbounds i8, i8* %17, i32 1, !dbg !419
  store i8* %incdec.ptr16, i8** %s, align 8, !dbg !419
  br label %if.end17

if.end17:                                         ; preds = %if.else13
  br label %if.end18

if.end18:                                         ; preds = %if.end17, %if.end
  br label %for.cond, !dbg !420

for.end:                                          ; preds = %if.then12, %for.cond
  %18 = load i8*, i8** %s, align 8, !dbg !422
  %19 = load i8, i8* %18, align 1, !dbg !424
  %conv19 = sext i8 %19 to i32, !dbg !424
  %cmp20 = icmp ne i32 %conv19, 34, !dbg !425
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !426

if.then22:                                        ; preds = %for.end
  store i64 -25, i64* %retval, align 8, !dbg !427
  br label %return, !dbg !427

if.end23:                                         ; preds = %for.end
  %20 = load i8*, i8** %s, align 8, !dbg !428
  %add.ptr24 = getelementptr inbounds i8, i8* %20, i64 1, !dbg !429
  %21 = load i8*, i8** %p.addr, align 8, !dbg !430
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr24 to i64, !dbg !431
  %sub.ptr.rhs.cast = ptrtoint i8* %21 to i64, !dbg !431
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !431
  store i64 %sub.ptr.sub, i64* %retval, align 8, !dbg !432
  br label %return, !dbg !432

return:                                           ; preds = %if.end23, %if.then22
  %22 = load i64, i64* %retval, align 8, !dbg !433
  ret i64 %22, !dbg !433
}

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #4

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #2

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #4

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly }
attributes #6 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!49, !50}
!llvm.ident = !{!51}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !21)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_cmdline.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !16}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_cmdline", file: !7, line: 37, size: 192, align: 64, elements: !8)
!7 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_cmdline_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!8 = !{!9, !12, !14}
!9 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !6, file: !7, line: 38, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!12 = !DIDerivedType(tag: DW_TAG_member, name: "argv", scope: !6, file: !7, line: 39, baseType: !13, size: 64, align: 64, offset: 64)
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "argc", scope: !6, file: !7, line: 40, baseType: !15, size: 32, align: 32, offset: 128)
!15 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !17, line: 109, baseType: !18)
!17 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !19, line: 172, baseType: !20)
!19 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!20 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!21 = !{!22, !27, !30, !33, !46, !47, !48}
!22 = distinct !DISubprogram(name: "__archive_cmdline_parse", scope: !1, file: !1, line: 109, type: !23, isLocal: false, isDefinition: true, scopeLine: 110, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!23 = !DISubroutineType(types: !24)
!24 = !{!15, !5, !25}
!25 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!26 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !11)
!27 = distinct !DISubprogram(name: "__archive_cmdline_allocate", scope: !1, file: !1, line: 202, type: !28, isLocal: false, isDefinition: true, scopeLine: 203, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!28 = !DISubroutineType(types: !29)
!29 = !{!5}
!30 = distinct !DISubprogram(name: "__archive_cmdline_free", scope: !1, file: !1, line: 212, type: !31, isLocal: false, isDefinition: true, scopeLine: 213, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = !DISubroutineType(types: !32)
!32 = !{!15, !5}
!33 = distinct !DISubprogram(name: "get_argument", scope: !1, file: !1, line: 69, type: !34, isLocal: true, isDefinition: true, scopeLine: 70, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!34 = !DISubroutineType(types: !35)
!35 = !{!16, !36, !25}
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !38, line: 58, size: 192, align: 64, elements: !39)
!38 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!39 = !{!40, !41, !45}
!40 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !37, file: !38, line: 59, baseType: !10, size: 64, align: 64)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !37, file: !38, line: 60, baseType: !42, size: 64, align: 64, offset: 64)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !43, line: 62, baseType: !44)
!43 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!44 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !37, file: !38, line: 61, baseType: !42, size: 64, align: 64, offset: 128)
!46 = distinct !DISubprogram(name: "extract_quotation", scope: !1, file: !1, line: 45, type: !34, isLocal: true, isDefinition: true, scopeLine: 46, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!47 = distinct !DISubprogram(name: "cmdline_set_path", scope: !1, file: !1, line: 166, type: !23, isLocal: true, isDefinition: true, scopeLine: 167, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!48 = distinct !DISubprogram(name: "cmdline_add_arg", scope: !1, file: !1, line: 182, type: !23, isLocal: true, isDefinition: true, scopeLine: 183, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!49 = !{i32 2, !"Dwarf Version", i32 4}
!50 = !{i32 2, !"Debug Info Version", i32 3}
!51 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!52 = !DILocalVariable(name: "data", arg: 1, scope: !22, file: !1, line: 109, type: !5)
!53 = !DIExpression()
!54 = !DILocation(line: 109, column: 49, scope: !22)
!55 = !DILocalVariable(name: "cmd", arg: 2, scope: !22, file: !1, line: 109, type: !25)
!56 = !DILocation(line: 109, column: 67, scope: !22)
!57 = !DILocalVariable(name: "as", scope: !22, file: !1, line: 111, type: !37)
!58 = !DILocation(line: 111, column: 24, scope: !22)
!59 = !DILocalVariable(name: "p", scope: !22, file: !1, line: 112, type: !25)
!60 = !DILocation(line: 112, column: 14, scope: !22)
!61 = !DILocalVariable(name: "al", scope: !22, file: !1, line: 113, type: !16)
!62 = !DILocation(line: 113, column: 10, scope: !22)
!63 = !DILocalVariable(name: "r", scope: !22, file: !1, line: 114, type: !15)
!64 = !DILocation(line: 114, column: 6, scope: !22)
!65 = !DILocation(line: 116, column: 2, scope: !22)
!66 = !DILocation(line: 116, column: 2, scope: !67)
!67 = !DILexicalBlockFile(scope: !68, file: !1, discriminator: 1)
!68 = distinct !DILexicalBlock(scope: !22, file: !1, line: 116, column: 2)
!69 = !DILocation(line: 119, column: 25, scope: !22)
!70 = !DILocation(line: 119, column: 7, scope: !22)
!71 = !DILocation(line: 119, column: 5, scope: !22)
!72 = !DILocation(line: 120, column: 6, scope: !73)
!73 = distinct !DILexicalBlock(scope: !22, file: !1, line: 120, column: 6)
!74 = !DILocation(line: 120, column: 9, scope: !73)
!75 = !DILocation(line: 120, column: 6, scope: !22)
!76 = !DILocation(line: 121, column: 5, scope: !77)
!77 = distinct !DILexicalBlock(scope: !73, file: !1, line: 120, column: 14)
!78 = !DILocation(line: 122, column: 3, scope: !77)
!79 = !DILocation(line: 124, column: 6, scope: !80)
!80 = distinct !DILexicalBlock(scope: !22, file: !1, line: 124, column: 6)
!81 = !DILocation(line: 124, column: 26, scope: !80)
!82 = !DILocation(line: 124, column: 6, scope: !22)
!83 = !DILocation(line: 125, column: 5, scope: !84)
!84 = distinct !DILexicalBlock(scope: !80, file: !1, line: 124, column: 32)
!85 = !DILocation(line: 126, column: 3, scope: !84)
!86 = !DILocation(line: 128, column: 23, scope: !22)
!87 = !DILocation(line: 128, column: 32, scope: !22)
!88 = !DILocation(line: 128, column: 6, scope: !22)
!89 = !DILocation(line: 128, column: 4, scope: !22)
!90 = !DILocation(line: 129, column: 6, scope: !91)
!91 = distinct !DILexicalBlock(scope: !22, file: !1, line: 129, column: 6)
!92 = !DILocation(line: 129, column: 8, scope: !91)
!93 = !DILocation(line: 129, column: 6, scope: !22)
!94 = !DILocation(line: 130, column: 3, scope: !91)
!95 = !DILocation(line: 131, column: 17, scope: !22)
!96 = !DILocation(line: 131, column: 6, scope: !22)
!97 = !DILocation(line: 131, column: 4, scope: !22)
!98 = !DILocation(line: 132, column: 6, scope: !99)
!99 = distinct !DILexicalBlock(scope: !22, file: !1, line: 132, column: 6)
!100 = !DILocation(line: 132, column: 8, scope: !99)
!101 = !DILocation(line: 132, column: 6, scope: !22)
!102 = !DILocation(line: 133, column: 10, scope: !99)
!103 = !DILocation(line: 133, column: 5, scope: !99)
!104 = !DILocation(line: 133, column: 3, scope: !99)
!105 = !DILocation(line: 135, column: 4, scope: !99)
!106 = !DILocation(line: 136, column: 22, scope: !22)
!107 = !DILocation(line: 136, column: 28, scope: !22)
!108 = !DILocation(line: 136, column: 6, scope: !22)
!109 = !DILocation(line: 136, column: 4, scope: !22)
!110 = !DILocation(line: 137, column: 6, scope: !111)
!111 = distinct !DILexicalBlock(scope: !22, file: !1, line: 137, column: 6)
!112 = !DILocation(line: 137, column: 8, scope: !111)
!113 = !DILocation(line: 137, column: 6, scope: !22)
!114 = !DILocation(line: 138, column: 3, scope: !111)
!115 = !DILocation(line: 139, column: 9, scope: !22)
!116 = !DILocation(line: 139, column: 6, scope: !22)
!117 = !DILocation(line: 141, column: 2, scope: !22)
!118 = !DILocation(line: 142, column: 26, scope: !119)
!119 = distinct !DILexicalBlock(scope: !120, file: !1, line: 141, column: 11)
!120 = distinct !DILexicalBlock(scope: !121, file: !1, line: 141, column: 2)
!121 = distinct !DILexicalBlock(scope: !22, file: !1, line: 141, column: 2)
!122 = !DILocation(line: 142, column: 8, scope: !119)
!123 = !DILocation(line: 142, column: 6, scope: !119)
!124 = !DILocation(line: 143, column: 7, scope: !125)
!125 = distinct !DILexicalBlock(scope: !119, file: !1, line: 143, column: 7)
!126 = !DILocation(line: 143, column: 10, scope: !125)
!127 = !DILocation(line: 143, column: 7, scope: !119)
!128 = !DILocation(line: 144, column: 6, scope: !129)
!129 = distinct !DILexicalBlock(scope: !125, file: !1, line: 143, column: 15)
!130 = !DILocation(line: 145, column: 4, scope: !129)
!131 = !DILocation(line: 147, column: 7, scope: !132)
!132 = distinct !DILexicalBlock(scope: !119, file: !1, line: 147, column: 7)
!133 = !DILocation(line: 147, column: 10, scope: !132)
!134 = !DILocation(line: 147, column: 7, scope: !119)
!135 = !DILocation(line: 148, column: 4, scope: !132)
!136 = !DILocation(line: 149, column: 10, scope: !119)
!137 = !DILocation(line: 149, column: 7, scope: !119)
!138 = !DILocation(line: 150, column: 7, scope: !139)
!139 = distinct !DILexicalBlock(scope: !119, file: !1, line: 150, column: 7)
!140 = !DILocation(line: 150, column: 27, scope: !139)
!141 = !DILocation(line: 150, column: 32, scope: !139)
!142 = !DILocation(line: 150, column: 36, scope: !143)
!143 = !DILexicalBlockFile(scope: !139, file: !1, discriminator: 1)
!144 = !DILocation(line: 150, column: 35, scope: !143)
!145 = !DILocation(line: 150, column: 40, scope: !143)
!146 = !DILocation(line: 150, column: 7, scope: !143)
!147 = !DILocation(line: 151, column: 4, scope: !139)
!148 = !DILocation(line: 152, column: 23, scope: !119)
!149 = !DILocation(line: 152, column: 32, scope: !119)
!150 = !DILocation(line: 152, column: 7, scope: !119)
!151 = !DILocation(line: 152, column: 5, scope: !119)
!152 = !DILocation(line: 153, column: 7, scope: !153)
!153 = distinct !DILexicalBlock(scope: !119, file: !1, line: 153, column: 7)
!154 = !DILocation(line: 153, column: 9, scope: !153)
!155 = !DILocation(line: 153, column: 7, scope: !119)
!156 = !DILocation(line: 154, column: 4, scope: !153)
!157 = !DILocation(line: 141, column: 2, scope: !158)
!158 = !DILexicalBlockFile(scope: !120, file: !1, discriminator: 1)
!159 = !DILocation(line: 156, column: 4, scope: !22)
!160 = !DILocation(line: 156, column: 2, scope: !22)
!161 = !DILocation(line: 158, column: 2, scope: !22)
!162 = !DILocation(line: 159, column: 10, scope: !22)
!163 = !DILocation(line: 159, column: 2, scope: !22)
!164 = !DILocalVariable(name: "as", arg: 1, scope: !33, file: !1, line: 69, type: !36)
!165 = !DILocation(line: 69, column: 37, scope: !33)
!166 = !DILocalVariable(name: "p", arg: 2, scope: !33, file: !1, line: 69, type: !25)
!167 = !DILocation(line: 69, column: 53, scope: !33)
!168 = !DILocalVariable(name: "s", scope: !33, file: !1, line: 71, type: !25)
!169 = !DILocation(line: 71, column: 14, scope: !33)
!170 = !DILocation(line: 71, column: 18, scope: !33)
!171 = !DILocation(line: 73, column: 2, scope: !33)
!172 = !DILocation(line: 76, column: 2, scope: !33)
!173 = !DILocation(line: 76, column: 10, scope: !174)
!174 = !DILexicalBlockFile(scope: !33, file: !1, discriminator: 1)
!175 = !DILocation(line: 76, column: 9, scope: !174)
!176 = !DILocation(line: 76, column: 12, scope: !174)
!177 = !DILocation(line: 76, column: 20, scope: !174)
!178 = !DILocation(line: 76, column: 24, scope: !179)
!179 = !DILexicalBlockFile(scope: !33, file: !1, discriminator: 2)
!180 = !DILocation(line: 76, column: 23, scope: !179)
!181 = !DILocation(line: 76, column: 26, scope: !179)
!182 = !DILocation(line: 76, column: 2, scope: !183)
!183 = !DILexicalBlockFile(scope: !33, file: !1, discriminator: 3)
!184 = !DILocation(line: 77, column: 4, scope: !33)
!185 = !DILocation(line: 76, column: 2, scope: !186)
!186 = !DILexicalBlockFile(scope: !33, file: !1, discriminator: 4)
!187 = !DILocation(line: 79, column: 2, scope: !33)
!188 = !DILocation(line: 79, column: 10, scope: !174)
!189 = !DILocation(line: 79, column: 9, scope: !174)
!190 = !DILocation(line: 79, column: 12, scope: !174)
!191 = !DILocation(line: 79, column: 20, scope: !174)
!192 = !DILocation(line: 79, column: 24, scope: !179)
!193 = !DILocation(line: 79, column: 23, scope: !179)
!194 = !DILocation(line: 79, column: 26, scope: !179)
!195 = !DILocation(line: 79, column: 2, scope: !183)
!196 = !DILocation(line: 80, column: 8, scope: !197)
!197 = distinct !DILexicalBlock(scope: !198, file: !1, line: 80, column: 7)
!198 = distinct !DILexicalBlock(scope: !33, file: !1, line: 79, column: 34)
!199 = !DILocation(line: 80, column: 7, scope: !197)
!200 = !DILocation(line: 80, column: 10, scope: !197)
!201 = !DILocation(line: 80, column: 7, scope: !198)
!202 = !DILocation(line: 81, column: 8, scope: !203)
!203 = distinct !DILexicalBlock(scope: !204, file: !1, line: 81, column: 8)
!204 = distinct !DILexicalBlock(scope: !197, file: !1, line: 80, column: 19)
!205 = !DILocation(line: 81, column: 13, scope: !203)
!206 = !DILocation(line: 81, column: 8, scope: !204)
!207 = !DILocation(line: 82, column: 28, scope: !208)
!208 = distinct !DILexicalBlock(scope: !203, file: !1, line: 81, column: 22)
!209 = !DILocation(line: 82, column: 32, scope: !208)
!210 = !DILocation(line: 82, column: 5, scope: !208)
!211 = !DILocation(line: 83, column: 7, scope: !208)
!212 = !DILocation(line: 84, column: 4, scope: !208)
!213 = !DILocation(line: 85, column: 6, scope: !214)
!214 = distinct !DILexicalBlock(scope: !203, file: !1, line: 84, column: 11)
!215 = !DILocation(line: 86, column: 5, scope: !214)
!216 = !DILocation(line: 88, column: 3, scope: !204)
!217 = !DILocation(line: 88, column: 15, scope: !218)
!218 = !DILexicalBlockFile(scope: !219, file: !1, discriminator: 1)
!219 = distinct !DILexicalBlock(scope: !197, file: !1, line: 88, column: 14)
!220 = !DILocation(line: 88, column: 14, scope: !218)
!221 = !DILocation(line: 88, column: 17, scope: !218)
!222 = !DILocalVariable(name: "q", scope: !223, file: !1, line: 89, type: !16)
!223 = distinct !DILexicalBlock(scope: !219, file: !1, line: 88, column: 25)
!224 = !DILocation(line: 89, column: 12, scope: !223)
!225 = !DILocation(line: 89, column: 34, scope: !223)
!226 = !DILocation(line: 89, column: 38, scope: !223)
!227 = !DILocation(line: 89, column: 16, scope: !223)
!228 = !DILocation(line: 90, column: 8, scope: !229)
!229 = distinct !DILexicalBlock(scope: !223, file: !1, line: 90, column: 8)
!230 = !DILocation(line: 90, column: 10, scope: !229)
!231 = !DILocation(line: 90, column: 8, scope: !223)
!232 = !DILocation(line: 91, column: 5, scope: !229)
!233 = !DILocation(line: 92, column: 9, scope: !223)
!234 = !DILocation(line: 92, column: 6, scope: !223)
!235 = !DILocation(line: 93, column: 3, scope: !223)
!236 = !DILocation(line: 94, column: 27, scope: !237)
!237 = distinct !DILexicalBlock(scope: !219, file: !1, line: 93, column: 10)
!238 = !DILocation(line: 94, column: 31, scope: !237)
!239 = !DILocation(line: 94, column: 4, scope: !237)
!240 = !DILocation(line: 95, column: 5, scope: !237)
!241 = !DILocation(line: 79, column: 2, scope: !186)
!242 = !DILocation(line: 98, column: 20, scope: !33)
!243 = !DILocation(line: 98, column: 24, scope: !33)
!244 = !DILocation(line: 98, column: 22, scope: !33)
!245 = !DILocation(line: 98, column: 2, scope: !33)
!246 = !DILocation(line: 99, column: 1, scope: !33)
!247 = !DILocalVariable(name: "data", arg: 1, scope: !47, file: !1, line: 166, type: !5)
!248 = !DILocation(line: 166, column: 42, scope: !47)
!249 = !DILocalVariable(name: "path", arg: 2, scope: !47, file: !1, line: 166, type: !25)
!250 = !DILocation(line: 166, column: 60, scope: !47)
!251 = !DILocalVariable(name: "newptr", scope: !47, file: !1, line: 168, type: !10)
!252 = !DILocation(line: 168, column: 8, scope: !47)
!253 = !DILocation(line: 170, column: 19, scope: !47)
!254 = !DILocation(line: 170, column: 25, scope: !47)
!255 = !DILocation(line: 170, column: 38, scope: !47)
!256 = !DILocation(line: 170, column: 31, scope: !47)
!257 = !DILocation(line: 170, column: 44, scope: !47)
!258 = !DILocation(line: 170, column: 11, scope: !259)
!259 = !DILexicalBlockFile(scope: !47, file: !1, discriminator: 1)
!260 = !DILocation(line: 170, column: 9, scope: !47)
!261 = !DILocation(line: 171, column: 6, scope: !262)
!262 = distinct !DILexicalBlock(scope: !47, file: !1, line: 171, column: 6)
!263 = !DILocation(line: 171, column: 13, scope: !262)
!264 = !DILocation(line: 171, column: 6, scope: !47)
!265 = !DILocation(line: 172, column: 3, scope: !262)
!266 = !DILocation(line: 173, column: 15, scope: !47)
!267 = !DILocation(line: 173, column: 2, scope: !47)
!268 = !DILocation(line: 173, column: 8, scope: !47)
!269 = !DILocation(line: 173, column: 13, scope: !47)
!270 = !DILocation(line: 174, column: 9, scope: !47)
!271 = !DILocation(line: 174, column: 15, scope: !47)
!272 = !DILocation(line: 174, column: 21, scope: !47)
!273 = !DILocation(line: 174, column: 2, scope: !47)
!274 = !DILocation(line: 175, column: 2, scope: !47)
!275 = !DILocation(line: 176, column: 1, scope: !47)
!276 = !DILocalVariable(name: "data", arg: 1, scope: !48, file: !1, line: 182, type: !5)
!277 = !DILocation(line: 182, column: 41, scope: !48)
!278 = !DILocalVariable(name: "arg", arg: 2, scope: !48, file: !1, line: 182, type: !25)
!279 = !DILocation(line: 182, column: 59, scope: !48)
!280 = !DILocalVariable(name: "newargv", scope: !48, file: !1, line: 184, type: !13)
!281 = !DILocation(line: 184, column: 9, scope: !48)
!282 = !DILocation(line: 186, column: 6, scope: !283)
!283 = distinct !DILexicalBlock(scope: !48, file: !1, line: 186, column: 6)
!284 = !DILocation(line: 186, column: 12, scope: !283)
!285 = !DILocation(line: 186, column: 17, scope: !283)
!286 = !DILocation(line: 186, column: 6, scope: !48)
!287 = !DILocation(line: 187, column: 3, scope: !283)
!288 = !DILocation(line: 189, column: 20, scope: !48)
!289 = !DILocation(line: 189, column: 26, scope: !48)
!290 = !DILocation(line: 189, column: 33, scope: !48)
!291 = !DILocation(line: 189, column: 39, scope: !48)
!292 = !DILocation(line: 189, column: 44, scope: !48)
!293 = !DILocation(line: 189, column: 32, scope: !48)
!294 = !DILocation(line: 189, column: 49, scope: !48)
!295 = !DILocation(line: 189, column: 12, scope: !48)
!296 = !DILocation(line: 189, column: 10, scope: !48)
!297 = !DILocation(line: 190, column: 6, scope: !298)
!298 = distinct !DILexicalBlock(scope: !48, file: !1, line: 190, column: 6)
!299 = !DILocation(line: 190, column: 14, scope: !298)
!300 = !DILocation(line: 190, column: 6, scope: !48)
!301 = !DILocation(line: 191, column: 3, scope: !298)
!302 = !DILocation(line: 192, column: 15, scope: !48)
!303 = !DILocation(line: 192, column: 2, scope: !48)
!304 = !DILocation(line: 192, column: 8, scope: !48)
!305 = !DILocation(line: 192, column: 13, scope: !48)
!306 = !DILocation(line: 193, column: 34, scope: !48)
!307 = !DILocation(line: 193, column: 27, scope: !48)
!308 = !DILocation(line: 193, column: 13, scope: !48)
!309 = !DILocation(line: 193, column: 19, scope: !48)
!310 = !DILocation(line: 193, column: 2, scope: !48)
!311 = !DILocation(line: 193, column: 8, scope: !48)
!312 = !DILocation(line: 193, column: 25, scope: !48)
!313 = !DILocation(line: 194, column: 17, scope: !314)
!314 = distinct !DILexicalBlock(scope: !48, file: !1, line: 194, column: 6)
!315 = !DILocation(line: 194, column: 23, scope: !314)
!316 = !DILocation(line: 194, column: 6, scope: !314)
!317 = !DILocation(line: 194, column: 12, scope: !314)
!318 = !DILocation(line: 194, column: 29, scope: !314)
!319 = !DILocation(line: 194, column: 6, scope: !48)
!320 = !DILocation(line: 195, column: 3, scope: !314)
!321 = !DILocation(line: 197, column: 15, scope: !48)
!322 = !DILocation(line: 197, column: 21, scope: !48)
!323 = !DILocation(line: 197, column: 13, scope: !48)
!324 = !DILocation(line: 197, column: 2, scope: !48)
!325 = !DILocation(line: 197, column: 8, scope: !48)
!326 = !DILocation(line: 197, column: 27, scope: !48)
!327 = !DILocation(line: 198, column: 2, scope: !48)
!328 = !DILocation(line: 199, column: 1, scope: !48)
!329 = !DILocation(line: 205, column: 3, scope: !27)
!330 = !DILocation(line: 204, column: 9, scope: !27)
!331 = !DILocation(line: 204, column: 2, scope: !27)
!332 = !DILocalVariable(name: "data", arg: 1, scope: !30, file: !1, line: 212, type: !5)
!333 = !DILocation(line: 212, column: 48, scope: !30)
!334 = !DILocation(line: 215, column: 6, scope: !335)
!335 = distinct !DILexicalBlock(scope: !30, file: !1, line: 215, column: 6)
!336 = !DILocation(line: 215, column: 6, scope: !30)
!337 = !DILocation(line: 216, column: 8, scope: !338)
!338 = distinct !DILexicalBlock(scope: !335, file: !1, line: 215, column: 12)
!339 = !DILocation(line: 216, column: 14, scope: !338)
!340 = !DILocation(line: 216, column: 3, scope: !338)
!341 = !DILocation(line: 217, column: 7, scope: !342)
!342 = distinct !DILexicalBlock(scope: !338, file: !1, line: 217, column: 7)
!343 = !DILocation(line: 217, column: 13, scope: !342)
!344 = !DILocation(line: 217, column: 18, scope: !342)
!345 = !DILocation(line: 217, column: 7, scope: !338)
!346 = !DILocalVariable(name: "i", scope: !347, file: !1, line: 218, type: !15)
!347 = distinct !DILexicalBlock(scope: !342, file: !1, line: 217, column: 27)
!348 = !DILocation(line: 218, column: 8, scope: !347)
!349 = !DILocation(line: 219, column: 11, scope: !350)
!350 = distinct !DILexicalBlock(scope: !347, file: !1, line: 219, column: 4)
!351 = !DILocation(line: 219, column: 9, scope: !350)
!352 = !DILocation(line: 219, column: 27, scope: !353)
!353 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 1)
!354 = distinct !DILexicalBlock(scope: !350, file: !1, line: 219, column: 4)
!355 = !DILocation(line: 219, column: 16, scope: !353)
!356 = !DILocation(line: 219, column: 22, scope: !353)
!357 = !DILocation(line: 219, column: 30, scope: !353)
!358 = !DILocation(line: 219, column: 4, scope: !353)
!359 = !DILocation(line: 220, column: 21, scope: !354)
!360 = !DILocation(line: 220, column: 10, scope: !354)
!361 = !DILocation(line: 220, column: 16, scope: !354)
!362 = !DILocation(line: 220, column: 5, scope: !354)
!363 = !DILocation(line: 219, column: 40, scope: !364)
!364 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 2)
!365 = !DILocation(line: 219, column: 4, scope: !364)
!366 = !DILocation(line: 221, column: 9, scope: !347)
!367 = !DILocation(line: 221, column: 15, scope: !347)
!368 = !DILocation(line: 221, column: 4, scope: !347)
!369 = !DILocation(line: 222, column: 3, scope: !347)
!370 = !DILocation(line: 223, column: 8, scope: !338)
!371 = !DILocation(line: 223, column: 3, scope: !338)
!372 = !DILocation(line: 224, column: 2, scope: !338)
!373 = !DILocation(line: 225, column: 2, scope: !30)
!374 = !DILocalVariable(name: "as", arg: 1, scope: !46, file: !1, line: 45, type: !36)
!375 = !DILocation(line: 45, column: 42, scope: !46)
!376 = !DILocalVariable(name: "p", arg: 2, scope: !46, file: !1, line: 45, type: !25)
!377 = !DILocation(line: 45, column: 58, scope: !46)
!378 = !DILocalVariable(name: "s", scope: !46, file: !1, line: 47, type: !25)
!379 = !DILocation(line: 47, column: 14, scope: !46)
!380 = !DILocation(line: 49, column: 11, scope: !381)
!381 = distinct !DILexicalBlock(scope: !46, file: !1, line: 49, column: 2)
!382 = !DILocation(line: 49, column: 13, scope: !381)
!383 = !DILocation(line: 49, column: 9, scope: !381)
!384 = !DILocation(line: 49, column: 7, scope: !381)
!385 = !DILocation(line: 49, column: 19, scope: !386)
!386 = !DILexicalBlockFile(scope: !387, file: !1, discriminator: 1)
!387 = distinct !DILexicalBlock(scope: !381, file: !1, line: 49, column: 2)
!388 = !DILocation(line: 49, column: 18, scope: !386)
!389 = !DILocation(line: 49, column: 2, scope: !386)
!390 = !DILocation(line: 50, column: 8, scope: !391)
!391 = distinct !DILexicalBlock(scope: !392, file: !1, line: 50, column: 7)
!392 = distinct !DILexicalBlock(scope: !387, file: !1, line: 49, column: 23)
!393 = !DILocation(line: 50, column: 7, scope: !391)
!394 = !DILocation(line: 50, column: 10, scope: !391)
!395 = !DILocation(line: 50, column: 7, scope: !392)
!396 = !DILocation(line: 51, column: 8, scope: !397)
!397 = distinct !DILexicalBlock(scope: !398, file: !1, line: 51, column: 8)
!398 = distinct !DILexicalBlock(scope: !391, file: !1, line: 50, column: 19)
!399 = !DILocation(line: 51, column: 13, scope: !397)
!400 = !DILocation(line: 51, column: 8, scope: !398)
!401 = !DILocation(line: 52, column: 28, scope: !402)
!402 = distinct !DILexicalBlock(scope: !397, file: !1, line: 51, column: 22)
!403 = !DILocation(line: 52, column: 32, scope: !402)
!404 = !DILocation(line: 52, column: 5, scope: !402)
!405 = !DILocation(line: 53, column: 7, scope: !402)
!406 = !DILocation(line: 54, column: 4, scope: !402)
!407 = !DILocation(line: 55, column: 6, scope: !397)
!408 = !DILocation(line: 56, column: 3, scope: !398)
!409 = !DILocation(line: 56, column: 15, scope: !410)
!410 = !DILexicalBlockFile(scope: !411, file: !1, discriminator: 1)
!411 = distinct !DILexicalBlock(scope: !391, file: !1, line: 56, column: 14)
!412 = !DILocation(line: 56, column: 14, scope: !410)
!413 = !DILocation(line: 56, column: 17, scope: !410)
!414 = !DILocation(line: 57, column: 4, scope: !411)
!415 = !DILocation(line: 59, column: 27, scope: !416)
!416 = distinct !DILexicalBlock(scope: !411, file: !1, line: 58, column: 8)
!417 = !DILocation(line: 59, column: 31, scope: !416)
!418 = !DILocation(line: 59, column: 4, scope: !416)
!419 = !DILocation(line: 60, column: 5, scope: !416)
!420 = !DILocation(line: 49, column: 2, scope: !421)
!421 = !DILexicalBlockFile(scope: !387, file: !1, discriminator: 2)
!422 = !DILocation(line: 63, column: 7, scope: !423)
!423 = distinct !DILexicalBlock(scope: !46, file: !1, line: 63, column: 6)
!424 = !DILocation(line: 63, column: 6, scope: !423)
!425 = !DILocation(line: 63, column: 9, scope: !423)
!426 = !DILocation(line: 63, column: 6, scope: !46)
!427 = !DILocation(line: 64, column: 3, scope: !423)
!428 = !DILocation(line: 65, column: 20, scope: !46)
!429 = !DILocation(line: 65, column: 22, scope: !46)
!430 = !DILocation(line: 65, column: 28, scope: !46)
!431 = !DILocation(line: 65, column: 26, scope: !46)
!432 = !DILocation(line: 65, column: 2, scope: !46)
!433 = !DILocation(line: 66, column: 1, scope: !46)
