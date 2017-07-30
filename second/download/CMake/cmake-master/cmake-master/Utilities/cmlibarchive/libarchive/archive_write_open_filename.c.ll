; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_open_filename.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.write_file_data = type { i32, %struct.archive_mstring }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }

@.str = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.1 = private unnamed_addr constant [26 x i8] c"Can't convert '%s' to WCS\00", align 1
@.str.2 = private unnamed_addr constant [26 x i8] c"Can't convert '%S' to MBS\00", align 1
@.str.3 = private unnamed_addr constant [20 x i8] c"Failed to open '%s'\00", align 1
@.str.4 = private unnamed_addr constant [20 x i8] c"Failed to open '%S'\00", align 1
@.str.5 = private unnamed_addr constant [19 x i8] c"Couldn't stat '%s'\00", align 1
@.str.6 = private unnamed_addr constant [19 x i8] c"Couldn't stat '%S'\00", align 1
@.str.7 = private unnamed_addr constant [12 x i8] c"Write error\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_open_file(%struct.archive* %a, i8* %filename) #0 !dbg !41 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %filename.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !148, metadata !149), !dbg !150
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !151, metadata !149), !dbg !152
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !153
  %1 = load i8*, i8** %filename.addr, align 8, !dbg !154
  %call = call i32 @archive_write_open_filename(%struct.archive* %0, i8* %1), !dbg !155
  ret i32 %call, !dbg !156
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_write_open_filename(%struct.archive* %a, i8* %filename) #0 !dbg !131 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %filename.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !157, metadata !149), !dbg !158
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !159, metadata !149), !dbg !160
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !161
  %cmp = icmp eq i8* %0, null, !dbg !163
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !164

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %filename.addr, align 8, !dbg !165
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !165
  %2 = load i8, i8* %arrayidx, align 1, !dbg !165
  %conv = sext i8 %2 to i32, !dbg !165
  %cmp1 = icmp eq i32 %conv, 0, !dbg !167
  br i1 %cmp1, label %if.then, label %if.end, !dbg !168

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !169
  %call = call i32 @archive_write_open_fd(%struct.archive* %3, i32 1), !dbg !170
  store i32 %call, i32* %retval, align 4, !dbg !171
  br label %return, !dbg !171

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !172
  %5 = load i8*, i8** %filename.addr, align 8, !dbg !173
  %call3 = call i32 @open_filename(%struct.archive* %4, i32 1, i8* %5), !dbg !174
  store i32 %call3, i32* %retval, align 4, !dbg !175
  br label %return, !dbg !175

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !176
  ret i32 %6, !dbg !176
}

declare i32 @archive_write_open_fd(%struct.archive*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @open_filename(%struct.archive* %a, i32 %mbs_fn, i8* %filename) #0 !dbg !135 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %mbs_fn.addr = alloca i32, align 4
  %filename.addr = alloca i8*, align 8
  %mine = alloca %struct.write_file_data*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !177, metadata !149), !dbg !178
  store i32 %mbs_fn, i32* %mbs_fn.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mbs_fn.addr, metadata !179, metadata !149), !dbg !180
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !181, metadata !149), !dbg !182
  call void @llvm.dbg.declare(metadata %struct.write_file_data** %mine, metadata !183, metadata !149), !dbg !184
  call void @llvm.dbg.declare(metadata i32* %r, metadata !185, metadata !149), !dbg !186
  %call = call noalias i8* @calloc(i64 1, i64 112) #5, !dbg !187
  %0 = bitcast i8* %call to %struct.write_file_data*, !dbg !188
  store %struct.write_file_data* %0, %struct.write_file_data** %mine, align 8, !dbg !189
  %1 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !190
  %cmp = icmp eq %struct.write_file_data* %1, null, !dbg !192
  br i1 %cmp, label %if.then, label %if.end, !dbg !193

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !194
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %2, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !196
  store i32 -30, i32* %retval, align 4, !dbg !197
  br label %return, !dbg !197

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %mbs_fn.addr, align 4, !dbg !198
  %tobool = icmp ne i32 %3, 0, !dbg !198
  br i1 %tobool, label %if.then1, label %if.else, !dbg !200

if.then1:                                         ; preds = %if.end
  %4 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !201
  %filename2 = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %4, i32 0, i32 1, !dbg !202
  %5 = load i8*, i8** %filename.addr, align 8, !dbg !203
  %call3 = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %filename2, i8* %5), !dbg !204
  store i32 %call3, i32* %r, align 4, !dbg !205
  br label %if.end6, !dbg !206

if.else:                                          ; preds = %if.end
  %6 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !207
  %filename4 = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %6, i32 0, i32 1, !dbg !208
  %7 = load i8*, i8** %filename.addr, align 8, !dbg !209
  %8 = bitcast i8* %7 to i32*, !dbg !209
  %call5 = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %filename4, i32* %8), !dbg !210
  store i32 %call5, i32* %r, align 4, !dbg !211
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.then1
  %9 = load i32, i32* %r, align 4, !dbg !212
  %cmp7 = icmp slt i32 %9, 0, !dbg !214
  br i1 %cmp7, label %if.then8, label %if.end17, !dbg !215

if.then8:                                         ; preds = %if.end6
  %call9 = call i32* @__errno_location() #1, !dbg !216
  %10 = load i32, i32* %call9, align 4, !dbg !216
  %cmp10 = icmp eq i32 %10, 12, !dbg !219
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !220

if.then11:                                        ; preds = %if.then8
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !221
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %11, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !223
  store i32 -30, i32* %retval, align 4, !dbg !224
  br label %return, !dbg !224

if.end12:                                         ; preds = %if.then8
  %12 = load i32, i32* %mbs_fn.addr, align 4, !dbg !225
  %tobool13 = icmp ne i32 %12, 0, !dbg !225
  br i1 %tobool13, label %if.then14, label %if.else15, !dbg !227

if.then14:                                        ; preds = %if.end12
  %13 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !228
  %14 = load i8*, i8** %filename.addr, align 8, !dbg !229
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %13, i32 -1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0), i8* %14), !dbg !230
  br label %if.end16, !dbg !230

if.else15:                                        ; preds = %if.end12
  %15 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !231
  %16 = load i8*, i8** %filename.addr, align 8, !dbg !232
  %17 = bitcast i8* %16 to i32*, !dbg !233
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %15, i32 -1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.2, i32 0, i32 0), i32* %17), !dbg !234
  br label %if.end16

if.end16:                                         ; preds = %if.else15, %if.then14
  store i32 -25, i32* %retval, align 4, !dbg !235
  br label %return, !dbg !235

if.end17:                                         ; preds = %if.end6
  %18 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !236
  %fd = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %18, i32 0, i32 0, !dbg !237
  store i32 -1, i32* %fd, align 8, !dbg !238
  %19 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !239
  %20 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !240
  %21 = bitcast %struct.write_file_data* %20 to i8*, !dbg !240
  %call18 = call i32 @archive_write_open(%struct.archive* %19, i8* %21, i32 (%struct.archive*, i8*)* @file_open, i64 (%struct.archive*, i8*, i8*, i64)* @file_write, i32 (%struct.archive*, i8*)* @file_close), !dbg !241
  store i32 %call18, i32* %retval, align 4, !dbg !242
  br label %return, !dbg !242

return:                                           ; preds = %if.end17, %if.end16, %if.then11, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !243
  ret i32 %22, !dbg !243
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_open_filename_w(%struct.archive* %a, i32* %filename) #0 !dbg !132 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %filename.addr = alloca i32*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !244, metadata !149), !dbg !245
  store i32* %filename, i32** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %filename.addr, metadata !246, metadata !149), !dbg !247
  %0 = load i32*, i32** %filename.addr, align 8, !dbg !248
  %cmp = icmp eq i32* %0, null, !dbg !250
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !251

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32*, i32** %filename.addr, align 8, !dbg !252
  %arrayidx = getelementptr inbounds i32, i32* %1, i64 0, !dbg !252
  %2 = load i32, i32* %arrayidx, align 4, !dbg !252
  %cmp1 = icmp eq i32 %2, 0, !dbg !254
  br i1 %cmp1, label %if.then, label %if.end, !dbg !255

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !256
  %call = call i32 @archive_write_open_fd(%struct.archive* %3, i32 1), !dbg !257
  store i32 %call, i32* %retval, align 4, !dbg !258
  br label %return, !dbg !258

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !259
  %5 = load i32*, i32** %filename.addr, align 8, !dbg !260
  %6 = bitcast i32* %5 to i8*, !dbg !260
  %call2 = call i32 @open_filename(%struct.archive* %4, i32 0, i8* %6), !dbg !261
  store i32 %call2, i32* %retval, align 4, !dbg !262
  br label %return, !dbg !262

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !263
  ret i32 %7, !dbg !263
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @archive_mstring_copy_mbs(%struct.archive_mstring*, i8*) #2

declare i32 @archive_mstring_copy_wcs(%struct.archive_mstring*, i32*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

declare i32 @archive_write_open(%struct.archive*, i8*, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_open(%struct.archive* %a, i8* %client_data) #0 !dbg !138 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %flags = alloca i32, align 4
  %mine = alloca %struct.write_file_data*, align 8
  %st = alloca %struct.stat, align 8
  %wcs = alloca i32*, align 8
  %mbs = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !264, metadata !149), !dbg !265
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !266, metadata !149), !dbg !267
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !268, metadata !149), !dbg !269
  call void @llvm.dbg.declare(metadata %struct.write_file_data** %mine, metadata !270, metadata !149), !dbg !271
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !272, metadata !149), !dbg !310
  call void @llvm.dbg.declare(metadata i32** %wcs, metadata !311, metadata !149), !dbg !312
  call void @llvm.dbg.declare(metadata i8** %mbs, metadata !313, metadata !149), !dbg !314
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !315
  %1 = bitcast i8* %0 to %struct.write_file_data*, !dbg !316
  store %struct.write_file_data* %1, %struct.write_file_data** %mine, align 8, !dbg !317
  store i32 524865, i32* %flags, align 4, !dbg !318
  store i8* null, i8** %mbs, align 8, !dbg !319
  store i32* null, i32** %wcs, align 8, !dbg !320
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !321
  %3 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !323
  %filename = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %3, i32 0, i32 1, !dbg !324
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %2, %struct.archive_mstring* %filename, i8** %mbs), !dbg !325
  %cmp = icmp ne i32 %call, 0, !dbg !326
  br i1 %cmp, label %if.then, label %if.end8, !dbg !327

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !328
  %4 = load i32, i32* %call1, align 4, !dbg !328
  %cmp2 = icmp eq i32 %4, 12, !dbg !331
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !332

if.then3:                                         ; preds = %if.then
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !333
  %call4 = call i32* @__errno_location() #1, !dbg !334
  %6 = load i32, i32* %call4, align 4, !dbg !334
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %5, i32 %6, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !335
  br label %if.end, !dbg !337

if.else:                                          ; preds = %if.then
  %7 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !338
  %8 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !340
  %filename5 = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %8, i32 0, i32 1, !dbg !341
  %call6 = call i32 @archive_mstring_get_wcs(%struct.archive* %7, %struct.archive_mstring* %filename5, i32** %wcs), !dbg !342
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !343
  %call7 = call i32* @__errno_location() #1, !dbg !344
  %10 = load i32, i32* %call7, align 4, !dbg !344
  %11 = load i32*, i32** %wcs, align 8, !dbg !345
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %9, i32 %10, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.2, i32 0, i32 0), i32* %11), !dbg !346
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then3
  store i32 -30, i32* %retval, align 4, !dbg !348
  br label %return, !dbg !348

if.end8:                                          ; preds = %entry
  %12 = load i8*, i8** %mbs, align 8, !dbg !349
  %13 = load i32, i32* %flags, align 4, !dbg !350
  %call9 = call i32 (i8*, i32, ...) @open(i8* %12, i32 %13, i32 438), !dbg !351
  %14 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !352
  %fd = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %14, i32 0, i32 0, !dbg !353
  store i32 %call9, i32* %fd, align 8, !dbg !354
  %15 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !355
  %fd10 = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %15, i32 0, i32 0, !dbg !356
  %16 = load i32, i32* %fd10, align 8, !dbg !356
  call void @__archive_ensure_cloexec_flag(i32 %16), !dbg !357
  %17 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !358
  %fd11 = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %17, i32 0, i32 0, !dbg !360
  %18 = load i32, i32* %fd11, align 8, !dbg !360
  %cmp12 = icmp slt i32 %18, 0, !dbg !361
  br i1 %cmp12, label %if.then13, label %if.end20, !dbg !362

if.then13:                                        ; preds = %if.end8
  %19 = load i8*, i8** %mbs, align 8, !dbg !363
  %cmp14 = icmp ne i8* %19, null, !dbg !366
  br i1 %cmp14, label %if.then15, label %if.else17, !dbg !367

if.then15:                                        ; preds = %if.then13
  %20 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !368
  %call16 = call i32* @__errno_location() #1, !dbg !369
  %21 = load i32, i32* %call16, align 4, !dbg !369
  %22 = load i8*, i8** %mbs, align 8, !dbg !370
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %20, i32 %21, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.3, i32 0, i32 0), i8* %22), !dbg !371
  br label %if.end19, !dbg !373

if.else17:                                        ; preds = %if.then13
  %23 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !374
  %call18 = call i32* @__errno_location() #1, !dbg !375
  %24 = load i32, i32* %call18, align 4, !dbg !375
  %25 = load i32*, i32** %wcs, align 8, !dbg !376
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %23, i32 %24, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.4, i32 0, i32 0), i32* %25), !dbg !377
  br label %if.end19

if.end19:                                         ; preds = %if.else17, %if.then15
  store i32 -30, i32* %retval, align 4, !dbg !378
  br label %return, !dbg !378

if.end20:                                         ; preds = %if.end8
  %26 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !379
  %fd21 = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %26, i32 0, i32 0, !dbg !381
  %27 = load i32, i32* %fd21, align 8, !dbg !381
  %call22 = call i32 @fstat(i32 %27, %struct.stat* %st) #5, !dbg !382
  %cmp23 = icmp ne i32 %call22, 0, !dbg !383
  br i1 %cmp23, label %if.then24, label %if.end31, !dbg !384

if.then24:                                        ; preds = %if.end20
  %28 = load i8*, i8** %mbs, align 8, !dbg !385
  %cmp25 = icmp ne i8* %28, null, !dbg !388
  br i1 %cmp25, label %if.then26, label %if.else28, !dbg !389

if.then26:                                        ; preds = %if.then24
  %29 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !390
  %call27 = call i32* @__errno_location() #1, !dbg !391
  %30 = load i32, i32* %call27, align 4, !dbg !391
  %31 = load i8*, i8** %mbs, align 8, !dbg !392
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %29, i32 %30, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.5, i32 0, i32 0), i8* %31), !dbg !393
  br label %if.end30, !dbg !395

if.else28:                                        ; preds = %if.then24
  %32 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !396
  %call29 = call i32* @__errno_location() #1, !dbg !397
  %33 = load i32, i32* %call29, align 4, !dbg !397
  %34 = load i32*, i32** %wcs, align 8, !dbg !398
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %32, i32 %33, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.6, i32 0, i32 0), i32* %34), !dbg !399
  br label %if.end30

if.end30:                                         ; preds = %if.else28, %if.then26
  store i32 -30, i32* %retval, align 4, !dbg !400
  br label %return, !dbg !400

if.end31:                                         ; preds = %if.end20
  %35 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !401
  %call32 = call i32 @archive_write_get_bytes_in_last_block(%struct.archive* %35), !dbg !403
  %cmp33 = icmp slt i32 %call32, 0, !dbg !404
  br i1 %cmp33, label %if.then34, label %if.end48, !dbg !405

if.then34:                                        ; preds = %if.end31
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !406
  %36 = load i32, i32* %st_mode, align 8, !dbg !406
  %and = and i32 %36, 61440, !dbg !406
  %cmp35 = icmp eq i32 %and, 8192, !dbg !406
  br i1 %cmp35, label %if.then43, label %lor.lhs.false, !dbg !409

lor.lhs.false:                                    ; preds = %if.then34
  %st_mode36 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !410
  %37 = load i32, i32* %st_mode36, align 8, !dbg !410
  %and37 = and i32 %37, 61440, !dbg !410
  %cmp38 = icmp eq i32 %and37, 24576, !dbg !410
  br i1 %cmp38, label %if.then43, label %lor.lhs.false39, !dbg !412

lor.lhs.false39:                                  ; preds = %lor.lhs.false
  %st_mode40 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !413
  %38 = load i32, i32* %st_mode40, align 8, !dbg !413
  %and41 = and i32 %38, 61440, !dbg !413
  %cmp42 = icmp eq i32 %and41, 4096, !dbg !413
  br i1 %cmp42, label %if.then43, label %if.else45, !dbg !414

if.then43:                                        ; preds = %lor.lhs.false39, %lor.lhs.false, %if.then34
  %39 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !416
  %call44 = call i32 @archive_write_set_bytes_in_last_block(%struct.archive* %39, i32 0), !dbg !417
  br label %if.end47, !dbg !417

if.else45:                                        ; preds = %lor.lhs.false39
  %40 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !418
  %call46 = call i32 @archive_write_set_bytes_in_last_block(%struct.archive* %40, i32 1), !dbg !419
  br label %if.end47

if.end47:                                         ; preds = %if.else45, %if.then43
  br label %if.end48, !dbg !420

if.end48:                                         ; preds = %if.end47, %if.end31
  %st_mode49 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !421
  %41 = load i32, i32* %st_mode49, align 8, !dbg !421
  %and50 = and i32 %41, 61440, !dbg !421
  %cmp51 = icmp eq i32 %and50, 32768, !dbg !421
  br i1 %cmp51, label %if.then52, label %if.end54, !dbg !423

if.then52:                                        ; preds = %if.end48
  %42 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !424
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 0, !dbg !425
  %43 = load i64, i64* %st_dev, align 8, !dbg !425
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 1, !dbg !426
  %44 = load i64, i64* %st_ino, align 8, !dbg !426
  %call53 = call i32 @archive_write_set_skip_file(%struct.archive* %42, i64 %43, i64 %44), !dbg !427
  br label %if.end54, !dbg !427

if.end54:                                         ; preds = %if.then52, %if.end48
  store i32 0, i32* %retval, align 4, !dbg !428
  br label %return, !dbg !428

return:                                           ; preds = %if.end54, %if.end30, %if.end19, %if.end
  %45 = load i32, i32* %retval, align 4, !dbg !429
  ret i32 %45, !dbg !429
}

; Function Attrs: nounwind uwtable
define internal i64 @file_write(%struct.archive* %a, i8* %client_data, i8* %buff, i64 %length) #0 !dbg !141 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %mine = alloca %struct.write_file_data*, align 8
  %bytesWritten = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !430, metadata !149), !dbg !431
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !432, metadata !149), !dbg !433
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !434, metadata !149), !dbg !435
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !436, metadata !149), !dbg !437
  call void @llvm.dbg.declare(metadata %struct.write_file_data** %mine, metadata !438, metadata !149), !dbg !439
  call void @llvm.dbg.declare(metadata i64* %bytesWritten, metadata !440, metadata !149), !dbg !441
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !442
  %1 = bitcast i8* %0 to %struct.write_file_data*, !dbg !443
  store %struct.write_file_data* %1, %struct.write_file_data** %mine, align 8, !dbg !444
  br label %for.cond, !dbg !445

for.cond:                                         ; preds = %if.then3, %entry
  %2 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !446
  %fd = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %2, i32 0, i32 0, !dbg !450
  %3 = load i32, i32* %fd, align 8, !dbg !450
  %4 = load i8*, i8** %buff.addr, align 8, !dbg !451
  %5 = load i64, i64* %length.addr, align 8, !dbg !452
  %call = call i64 @write(i32 %3, i8* %4, i64 %5), !dbg !453
  store i64 %call, i64* %bytesWritten, align 8, !dbg !454
  %6 = load i64, i64* %bytesWritten, align 8, !dbg !455
  %cmp = icmp sle i64 %6, 0, !dbg !457
  br i1 %cmp, label %if.then, label %if.end5, !dbg !458

if.then:                                          ; preds = %for.cond
  %call1 = call i32* @__errno_location() #1, !dbg !459
  %7 = load i32, i32* %call1, align 4, !dbg !459
  %cmp2 = icmp eq i32 %7, 4, !dbg !462
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !463

if.then3:                                         ; preds = %if.then
  br label %for.cond, !dbg !464

if.end:                                           ; preds = %if.then
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !465
  %call4 = call i32* @__errno_location() #1, !dbg !466
  %9 = load i32, i32* %call4, align 4, !dbg !466
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %8, i32 %9, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.7, i32 0, i32 0)), !dbg !467
  store i64 -1, i64* %retval, align 8, !dbg !469
  br label %return, !dbg !469

if.end5:                                          ; preds = %for.cond
  %10 = load i64, i64* %bytesWritten, align 8, !dbg !470
  store i64 %10, i64* %retval, align 8, !dbg !471
  br label %return, !dbg !471

return:                                           ; preds = %if.end5, %if.end
  %11 = load i64, i64* %retval, align 8, !dbg !472
  ret i64 %11, !dbg !472
}

; Function Attrs: nounwind uwtable
define internal i32 @file_close(%struct.archive* %a, i8* %client_data) #0 !dbg !144 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.write_file_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !473, metadata !149), !dbg !474
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !475, metadata !149), !dbg !476
  call void @llvm.dbg.declare(metadata %struct.write_file_data** %mine, metadata !477, metadata !149), !dbg !478
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !479
  %1 = bitcast i8* %0 to %struct.write_file_data*, !dbg !480
  store %struct.write_file_data* %1, %struct.write_file_data** %mine, align 8, !dbg !478
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !481
  %3 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !482
  %fd = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %3, i32 0, i32 0, !dbg !484
  %4 = load i32, i32* %fd, align 8, !dbg !484
  %cmp = icmp sge i32 %4, 0, !dbg !485
  br i1 %cmp, label %if.then, label %if.end, !dbg !486

if.then:                                          ; preds = %entry
  %5 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !487
  %fd1 = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %5, i32 0, i32 0, !dbg !488
  %6 = load i32, i32* %fd1, align 8, !dbg !488
  %call = call i32 @close(i32 %6), !dbg !489
  br label %if.end, !dbg !489

if.end:                                           ; preds = %if.then, %entry
  %7 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !490
  %filename = getelementptr inbounds %struct.write_file_data, %struct.write_file_data* %7, i32 0, i32 1, !dbg !491
  call void @archive_mstring_clean(%struct.archive_mstring* %filename), !dbg !492
  %8 = load %struct.write_file_data*, %struct.write_file_data** %mine, align 8, !dbg !493
  %9 = bitcast %struct.write_file_data* %8 to i8*, !dbg !493
  call void @free(i8* %9) #5, !dbg !494
  ret i32 0, !dbg !495
}

declare i32 @archive_mstring_get_mbs(%struct.archive*, %struct.archive_mstring*, i8**) #2

declare i32 @archive_mstring_get_wcs(%struct.archive*, %struct.archive_mstring*, i32**) #2

declare i32 @open(i8*, i32, ...) #2

declare void @__archive_ensure_cloexec_flag(i32) #2

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #3

declare i32 @archive_write_get_bytes_in_last_block(%struct.archive*) #2

declare i32 @archive_write_set_bytes_in_last_block(%struct.archive*, i32) #2

declare i32 @archive_write_set_skip_file(%struct.archive*, i64, i64) #2

declare i64 @write(i32, i8*, i64) #2

declare i32 @close(i32) #2

declare void @archive_mstring_clean(%struct.archive_mstring*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!145, !146}
!llvm.ident = !{!147}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !40)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_open_filename.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !36, !38}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "write_file_data", file: !1, line: 59, size: 896, align: 64, elements: !7)
!7 = !{!8, !10}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !6, file: !1, line: 60, baseType: !9, size: 32, align: 32)
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !6, file: !1, line: 61, baseType: !11, size: 832, align: 64, offset: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_mstring", file: !12, line: 209, size: 832, align: 64, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !25, !26, !34, !35}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs", scope: !11, file: !12, line: 210, baseType: !15, size: 192, align: 64)
!15 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !12, line: 58, size: 192, align: 64, elements: !16)
!16 = !{!17, !20, !24}
!17 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !15, file: !12, line: 59, baseType: !18, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !15, file: !12, line: 60, baseType: !21, size: 64, align: 64, offset: 64)
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !22, line: 62, baseType: !23)
!22 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!23 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !15, file: !12, line: 61, baseType: !21, size: 64, align: 64, offset: 128)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "aes_utf8", scope: !11, file: !12, line: 211, baseType: !15, size: 192, align: 64, offset: 192)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "aes_wcs", scope: !11, file: !12, line: 212, baseType: !27, size: 192, align: 64, offset: 384)
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !12, line: 64, size: 192, align: 64, elements: !28)
!28 = !{!29, !32, !33}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !27, file: !12, line: 65, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !22, line: 90, baseType: !9)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !27, file: !12, line: 66, baseType: !21, size: 64, align: 64, offset: 64)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !27, file: !12, line: 67, baseType: !21, size: 64, align: 64, offset: 128)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs_in_locale", scope: !11, file: !12, line: 213, baseType: !15, size: 192, align: 64, offset: 576)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "aes_set", scope: !11, file: !12, line: 218, baseType: !9, size: 32, align: 32, offset: 768)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !19)
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !31)
!40 = !{!41, !131, !132, !135, !138, !141, !144}
!41 = distinct !DISubprogram(name: "archive_write_open_file", scope: !1, file: !1, line: 70, type: !42, isLocal: false, isDefinition: true, scopeLine: 71, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!42 = !DISubroutineType(types: !43)
!43 = !{!9, !44, !36}
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !46, line: 89, size: 1280, align: 64, elements: !47)
!46 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !{!48, !50, !51, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !125, !126, !127, !128, !129, !130}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !45, file: !46, line: 96, baseType: !49, size: 32, align: 32)
!49 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !45, file: !46, line: 97, baseType: !49, size: 32, align: 32, offset: 32)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !45, file: !46, line: 103, baseType: !52, size: 64, align: 64, offset: 64)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !46, line: 63, size: 832, align: 64, elements: !54)
!54 = !{!55, !59, !60, !67, !68, !79, !85, !90, !91, !98, !99, !103, !107}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !53, file: !46, line: 64, baseType: !56, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DISubroutineType(types: !58)
!58 = !{!9, !44}
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !53, file: !46, line: 65, baseType: !56, size: 64, align: 64, offset: 64)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !53, file: !46, line: 66, baseType: !61, size: 64, align: 64, offset: 128)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!9, !44, !64}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!65 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !66, line: 180, flags: DIFlagFwdDecl)
!66 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !53, file: !46, line: 68, baseType: !56, size: 64, align: 64, offset: 192)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !53, file: !46, line: 69, baseType: !69, size: 64, align: 64, offset: 256)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!72, !44, !77, !21}
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !73, line: 109, baseType: !74)
!73 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!74 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !75, line: 172, baseType: !76)
!75 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!76 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !53, file: !46, line: 71, baseType: !80, size: 64, align: 64, offset: 320)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DISubroutineType(types: !82)
!82 = !{!72, !44, !77, !21, !83}
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !84, line: 40, baseType: !76)
!84 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!85 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !53, file: !46, line: 74, baseType: !86, size: 64, align: 64, offset: 384)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DISubroutineType(types: !88)
!88 = !{!9, !44, !89}
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !53, file: !46, line: 76, baseType: !61, size: 64, align: 64, offset: 448)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !53, file: !46, line: 78, baseType: !92, size: 64, align: 64, offset: 512)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DISubroutineType(types: !94)
!94 = !{!9, !44, !95, !96, !97}
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !53, file: !46, line: 81, baseType: !56, size: 64, align: 64, offset: 576)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !53, file: !46, line: 82, baseType: !100, size: 64, align: 64, offset: 640)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{!83, !44, !9}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !53, file: !46, line: 83, baseType: !104, size: 64, align: 64, offset: 704)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!9, !44, !9}
!107 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !53, file: !46, line: 84, baseType: !108, size: 64, align: 64, offset: 768)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DISubroutineType(types: !110)
!110 = !{!36, !44, !9}
!111 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !45, file: !46, line: 105, baseType: !9, size: 32, align: 32, offset: 128)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !45, file: !46, line: 106, baseType: !36, size: 64, align: 64, offset: 192)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !45, file: !46, line: 108, baseType: !9, size: 32, align: 32, offset: 256)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !45, file: !46, line: 109, baseType: !36, size: 64, align: 64, offset: 320)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !45, file: !46, line: 112, baseType: !9, size: 32, align: 32, offset: 384)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !45, file: !46, line: 114, baseType: !9, size: 32, align: 32, offset: 416)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !45, file: !46, line: 115, baseType: !36, size: 64, align: 64, offset: 448)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !45, file: !46, line: 116, baseType: !15, size: 192, align: 64, offset: 512)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !45, file: !46, line: 118, baseType: !18, size: 64, align: 64, offset: 704)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !45, file: !46, line: 119, baseType: !49, size: 32, align: 32, offset: 768)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !45, file: !46, line: 120, baseType: !49, size: 32, align: 32, offset: 800)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !45, file: !46, line: 121, baseType: !123, size: 64, align: 64, offset: 832)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !12, line: 70, flags: DIFlagFwdDecl)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !45, file: !46, line: 127, baseType: !36, size: 64, align: 64, offset: 896)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !45, file: !46, line: 128, baseType: !83, size: 64, align: 64, offset: 960)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !45, file: !46, line: 129, baseType: !83, size: 64, align: 64, offset: 1024)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !45, file: !46, line: 130, baseType: !21, size: 64, align: 64, offset: 1088)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !45, file: !46, line: 137, baseType: !19, size: 8, align: 8, offset: 1152)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !45, file: !46, line: 138, baseType: !21, size: 64, align: 64, offset: 1216)
!131 = distinct !DISubprogram(name: "archive_write_open_filename", scope: !1, file: !1, line: 76, type: !42, isLocal: false, isDefinition: true, scopeLine: 77, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!132 = distinct !DISubprogram(name: "archive_write_open_filename_w", scope: !1, file: !1, line: 86, type: !133, isLocal: false, isDefinition: true, scopeLine: 87, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!133 = !DISubroutineType(types: !134)
!134 = !{!9, !44, !38}
!135 = distinct !DISubprogram(name: "open_filename", scope: !1, file: !1, line: 96, type: !136, isLocal: true, isDefinition: true, scopeLine: 97, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!136 = !DISubroutineType(types: !137)
!137 = !{!9, !44, !9, !77}
!138 = distinct !DISubprogram(name: "file_open", scope: !1, file: !1, line: 131, type: !139, isLocal: true, isDefinition: true, scopeLine: 132, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!139 = !DISubroutineType(types: !140)
!140 = !{!9, !44, !4}
!141 = distinct !DISubprogram(name: "file_write", scope: !1, file: !1, line: 221, type: !142, isLocal: true, isDefinition: true, scopeLine: 223, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!142 = !DISubroutineType(types: !143)
!143 = !{!72, !44, !4, !77, !21}
!144 = distinct !DISubprogram(name: "file_close", scope: !1, file: !1, line: 241, type: !139, isLocal: true, isDefinition: true, scopeLine: 242, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!145 = !{i32 2, !"Dwarf Version", i32 4}
!146 = !{i32 2, !"Debug Info Version", i32 3}
!147 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!148 = !DILocalVariable(name: "a", arg: 1, scope: !41, file: !1, line: 70, type: !44)
!149 = !DIExpression()
!150 = !DILocation(line: 70, column: 41, scope: !41)
!151 = !DILocalVariable(name: "filename", arg: 2, scope: !41, file: !1, line: 70, type: !36)
!152 = !DILocation(line: 70, column: 56, scope: !41)
!153 = !DILocation(line: 72, column: 38, scope: !41)
!154 = !DILocation(line: 72, column: 41, scope: !41)
!155 = !DILocation(line: 72, column: 10, scope: !41)
!156 = !DILocation(line: 72, column: 2, scope: !41)
!157 = !DILocalVariable(name: "a", arg: 1, scope: !131, file: !1, line: 76, type: !44)
!158 = !DILocation(line: 76, column: 45, scope: !131)
!159 = !DILocalVariable(name: "filename", arg: 2, scope: !131, file: !1, line: 76, type: !36)
!160 = !DILocation(line: 76, column: 60, scope: !131)
!161 = !DILocation(line: 79, column: 6, scope: !162)
!162 = distinct !DILexicalBlock(scope: !131, file: !1, line: 79, column: 6)
!163 = !DILocation(line: 79, column: 15, scope: !162)
!164 = !DILocation(line: 79, column: 23, scope: !162)
!165 = !DILocation(line: 79, column: 26, scope: !166)
!166 = !DILexicalBlockFile(scope: !162, file: !1, discriminator: 1)
!167 = !DILocation(line: 79, column: 38, scope: !166)
!168 = !DILocation(line: 79, column: 6, scope: !166)
!169 = !DILocation(line: 80, column: 33, scope: !162)
!170 = !DILocation(line: 80, column: 11, scope: !162)
!171 = !DILocation(line: 80, column: 3, scope: !162)
!172 = !DILocation(line: 82, column: 24, scope: !131)
!173 = !DILocation(line: 82, column: 30, scope: !131)
!174 = !DILocation(line: 82, column: 10, scope: !131)
!175 = !DILocation(line: 82, column: 2, scope: !131)
!176 = !DILocation(line: 83, column: 1, scope: !131)
!177 = !DILocalVariable(name: "a", arg: 1, scope: !135, file: !1, line: 96, type: !44)
!178 = !DILocation(line: 96, column: 31, scope: !135)
!179 = !DILocalVariable(name: "mbs_fn", arg: 2, scope: !135, file: !1, line: 96, type: !9)
!180 = !DILocation(line: 96, column: 38, scope: !135)
!181 = !DILocalVariable(name: "filename", arg: 3, scope: !135, file: !1, line: 96, type: !77)
!182 = !DILocation(line: 96, column: 58, scope: !135)
!183 = !DILocalVariable(name: "mine", scope: !135, file: !1, line: 98, type: !5)
!184 = !DILocation(line: 98, column: 26, scope: !135)
!185 = !DILocalVariable(name: "r", scope: !135, file: !1, line: 99, type: !9)
!186 = !DILocation(line: 99, column: 6, scope: !135)
!187 = !DILocation(line: 101, column: 35, scope: !135)
!188 = !DILocation(line: 101, column: 9, scope: !135)
!189 = !DILocation(line: 101, column: 7, scope: !135)
!190 = !DILocation(line: 102, column: 6, scope: !191)
!191 = distinct !DILexicalBlock(scope: !135, file: !1, line: 102, column: 6)
!192 = !DILocation(line: 102, column: 11, scope: !191)
!193 = !DILocation(line: 102, column: 6, scope: !135)
!194 = !DILocation(line: 103, column: 21, scope: !195)
!195 = distinct !DILexicalBlock(scope: !191, file: !1, line: 102, column: 20)
!196 = !DILocation(line: 103, column: 3, scope: !195)
!197 = !DILocation(line: 104, column: 3, scope: !195)
!198 = !DILocation(line: 106, column: 6, scope: !199)
!199 = distinct !DILexicalBlock(scope: !135, file: !1, line: 106, column: 6)
!200 = !DILocation(line: 106, column: 6, scope: !135)
!201 = !DILocation(line: 107, column: 33, scope: !199)
!202 = !DILocation(line: 107, column: 39, scope: !199)
!203 = !DILocation(line: 107, column: 49, scope: !199)
!204 = !DILocation(line: 107, column: 7, scope: !199)
!205 = !DILocation(line: 107, column: 5, scope: !199)
!206 = !DILocation(line: 107, column: 3, scope: !199)
!207 = !DILocation(line: 109, column: 33, scope: !199)
!208 = !DILocation(line: 109, column: 39, scope: !199)
!209 = !DILocation(line: 109, column: 49, scope: !199)
!210 = !DILocation(line: 109, column: 7, scope: !199)
!211 = !DILocation(line: 109, column: 5, scope: !199)
!212 = !DILocation(line: 110, column: 6, scope: !213)
!213 = distinct !DILexicalBlock(scope: !135, file: !1, line: 110, column: 6)
!214 = !DILocation(line: 110, column: 8, scope: !213)
!215 = !DILocation(line: 110, column: 6, scope: !135)
!216 = !DILocation(line: 111, column: 7, scope: !217)
!217 = distinct !DILexicalBlock(scope: !218, file: !1, line: 111, column: 7)
!218 = distinct !DILexicalBlock(scope: !213, file: !1, line: 110, column: 13)
!219 = !DILocation(line: 111, column: 13, scope: !217)
!220 = !DILocation(line: 111, column: 7, scope: !218)
!221 = !DILocation(line: 112, column: 22, scope: !222)
!222 = distinct !DILexicalBlock(scope: !217, file: !1, line: 111, column: 24)
!223 = !DILocation(line: 112, column: 4, scope: !222)
!224 = !DILocation(line: 113, column: 4, scope: !222)
!225 = !DILocation(line: 115, column: 7, scope: !226)
!226 = distinct !DILexicalBlock(scope: !218, file: !1, line: 115, column: 7)
!227 = !DILocation(line: 115, column: 7, scope: !218)
!228 = !DILocation(line: 116, column: 22, scope: !226)
!229 = !DILocation(line: 118, column: 22, scope: !226)
!230 = !DILocation(line: 116, column: 4, scope: !226)
!231 = !DILocation(line: 120, column: 22, scope: !226)
!232 = !DILocation(line: 122, column: 25, scope: !226)
!233 = !DILocation(line: 122, column: 8, scope: !226)
!234 = !DILocation(line: 120, column: 4, scope: !226)
!235 = !DILocation(line: 123, column: 3, scope: !218)
!236 = !DILocation(line: 125, column: 2, scope: !135)
!237 = !DILocation(line: 125, column: 8, scope: !135)
!238 = !DILocation(line: 125, column: 11, scope: !135)
!239 = !DILocation(line: 126, column: 29, scope: !135)
!240 = !DILocation(line: 126, column: 32, scope: !135)
!241 = !DILocation(line: 126, column: 10, scope: !135)
!242 = !DILocation(line: 126, column: 2, scope: !135)
!243 = !DILocation(line: 128, column: 1, scope: !135)
!244 = !DILocalVariable(name: "a", arg: 1, scope: !132, file: !1, line: 86, type: !44)
!245 = !DILocation(line: 86, column: 47, scope: !132)
!246 = !DILocalVariable(name: "filename", arg: 2, scope: !132, file: !1, line: 86, type: !38)
!247 = !DILocation(line: 86, column: 65, scope: !132)
!248 = !DILocation(line: 89, column: 6, scope: !249)
!249 = distinct !DILexicalBlock(scope: !132, file: !1, line: 89, column: 6)
!250 = !DILocation(line: 89, column: 15, scope: !249)
!251 = !DILocation(line: 89, column: 23, scope: !249)
!252 = !DILocation(line: 89, column: 26, scope: !253)
!253 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 1)
!254 = !DILocation(line: 89, column: 38, scope: !253)
!255 = !DILocation(line: 89, column: 6, scope: !253)
!256 = !DILocation(line: 90, column: 33, scope: !249)
!257 = !DILocation(line: 90, column: 11, scope: !249)
!258 = !DILocation(line: 90, column: 3, scope: !249)
!259 = !DILocation(line: 92, column: 24, scope: !132)
!260 = !DILocation(line: 92, column: 30, scope: !132)
!261 = !DILocation(line: 92, column: 10, scope: !132)
!262 = !DILocation(line: 92, column: 2, scope: !132)
!263 = !DILocation(line: 93, column: 1, scope: !132)
!264 = !DILocalVariable(name: "a", arg: 1, scope: !138, file: !1, line: 131, type: !44)
!265 = !DILocation(line: 131, column: 27, scope: !138)
!266 = !DILocalVariable(name: "client_data", arg: 2, scope: !138, file: !1, line: 131, type: !4)
!267 = !DILocation(line: 131, column: 36, scope: !138)
!268 = !DILocalVariable(name: "flags", scope: !138, file: !1, line: 133, type: !9)
!269 = !DILocation(line: 133, column: 6, scope: !138)
!270 = !DILocalVariable(name: "mine", scope: !138, file: !1, line: 134, type: !5)
!271 = !DILocation(line: 134, column: 26, scope: !138)
!272 = !DILocalVariable(name: "st", scope: !138, file: !1, line: 135, type: !273)
!273 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !274, line: 46, size: 1152, align: 64, elements: !275)
!274 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!275 = !{!276, !278, !280, !282, !284, !286, !288, !289, !290, !292, !294, !296, !304, !305, !306}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !273, file: !274, line: 48, baseType: !277, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !75, line: 124, baseType: !23)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !273, file: !274, line: 53, baseType: !279, size: 64, align: 64, offset: 64)
!279 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !75, line: 127, baseType: !23)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !273, file: !274, line: 61, baseType: !281, size: 64, align: 64, offset: 128)
!281 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !75, line: 130, baseType: !23)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !273, file: !274, line: 62, baseType: !283, size: 32, align: 32, offset: 192)
!283 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !75, line: 129, baseType: !49)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !273, file: !274, line: 64, baseType: !285, size: 32, align: 32, offset: 224)
!285 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !75, line: 125, baseType: !49)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !273, file: !274, line: 65, baseType: !287, size: 32, align: 32, offset: 256)
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !75, line: 126, baseType: !49)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !273, file: !274, line: 67, baseType: !9, size: 32, align: 32, offset: 288)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !273, file: !274, line: 69, baseType: !277, size: 64, align: 64, offset: 320)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !273, file: !274, line: 74, baseType: !291, size: 64, align: 64, offset: 384)
!291 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !75, line: 131, baseType: !76)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !273, file: !274, line: 78, baseType: !293, size: 64, align: 64, offset: 448)
!293 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !75, line: 153, baseType: !76)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !273, file: !274, line: 80, baseType: !295, size: 64, align: 64, offset: 512)
!295 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !75, line: 158, baseType: !76)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !273, file: !274, line: 91, baseType: !297, size: 128, align: 64, offset: 576)
!297 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !298, line: 120, size: 128, align: 64, elements: !299)
!298 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!299 = !{!300, !302}
!300 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !297, file: !298, line: 122, baseType: !301, size: 64, align: 64)
!301 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !75, line: 139, baseType: !76)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !297, file: !298, line: 123, baseType: !303, size: 64, align: 64, offset: 64)
!303 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !75, line: 175, baseType: !76)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !273, file: !274, line: 92, baseType: !297, size: 128, align: 64, offset: 704)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !273, file: !274, line: 93, baseType: !297, size: 128, align: 64, offset: 832)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !273, file: !274, line: 106, baseType: !307, size: 192, align: 64, offset: 960)
!307 = !DICompositeType(tag: DW_TAG_array_type, baseType: !303, size: 192, align: 64, elements: !308)
!308 = !{!309}
!309 = !DISubrange(count: 3)
!310 = !DILocation(line: 135, column: 14, scope: !138)
!311 = !DILocalVariable(name: "wcs", scope: !138, file: !1, line: 139, type: !38)
!312 = !DILocation(line: 139, column: 17, scope: !138)
!313 = !DILocalVariable(name: "mbs", scope: !138, file: !1, line: 140, type: !36)
!314 = !DILocation(line: 140, column: 14, scope: !138)
!315 = !DILocation(line: 142, column: 35, scope: !138)
!316 = !DILocation(line: 142, column: 9, scope: !138)
!317 = !DILocation(line: 142, column: 7, scope: !138)
!318 = !DILocation(line: 143, column: 8, scope: !138)
!319 = !DILocation(line: 148, column: 6, scope: !138)
!320 = !DILocation(line: 148, column: 18, scope: !138)
!321 = !DILocation(line: 167, column: 30, scope: !322)
!322 = distinct !DILexicalBlock(scope: !138, file: !1, line: 167, column: 6)
!323 = !DILocation(line: 167, column: 34, scope: !322)
!324 = !DILocation(line: 167, column: 40, scope: !322)
!325 = !DILocation(line: 167, column: 6, scope: !322)
!326 = !DILocation(line: 167, column: 56, scope: !322)
!327 = !DILocation(line: 167, column: 6, scope: !138)
!328 = !DILocation(line: 168, column: 7, scope: !329)
!329 = distinct !DILexicalBlock(scope: !330, file: !1, line: 168, column: 7)
!330 = distinct !DILexicalBlock(scope: !322, file: !1, line: 167, column: 62)
!331 = !DILocation(line: 168, column: 13, scope: !329)
!332 = !DILocation(line: 168, column: 7, scope: !330)
!333 = !DILocation(line: 169, column: 22, scope: !329)
!334 = !DILocation(line: 169, column: 25, scope: !329)
!335 = !DILocation(line: 169, column: 4, scope: !336)
!336 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 1)
!337 = !DILocation(line: 169, column: 4, scope: !329)
!338 = !DILocation(line: 171, column: 28, scope: !339)
!339 = distinct !DILexicalBlock(scope: !329, file: !1, line: 170, column: 8)
!340 = !DILocation(line: 171, column: 32, scope: !339)
!341 = !DILocation(line: 171, column: 38, scope: !339)
!342 = !DILocation(line: 171, column: 4, scope: !339)
!343 = !DILocation(line: 172, column: 22, scope: !339)
!344 = !DILocation(line: 172, column: 25, scope: !339)
!345 = !DILocation(line: 173, column: 37, scope: !339)
!346 = !DILocation(line: 172, column: 4, scope: !347)
!347 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 1)
!348 = !DILocation(line: 175, column: 3, scope: !330)
!349 = !DILocation(line: 177, column: 18, scope: !138)
!350 = !DILocation(line: 177, column: 23, scope: !138)
!351 = !DILocation(line: 177, column: 13, scope: !138)
!352 = !DILocation(line: 177, column: 2, scope: !138)
!353 = !DILocation(line: 177, column: 8, scope: !138)
!354 = !DILocation(line: 177, column: 11, scope: !138)
!355 = !DILocation(line: 178, column: 32, scope: !138)
!356 = !DILocation(line: 178, column: 38, scope: !138)
!357 = !DILocation(line: 178, column: 2, scope: !138)
!358 = !DILocation(line: 180, column: 6, scope: !359)
!359 = distinct !DILexicalBlock(scope: !138, file: !1, line: 180, column: 6)
!360 = !DILocation(line: 180, column: 12, scope: !359)
!361 = !DILocation(line: 180, column: 15, scope: !359)
!362 = !DILocation(line: 180, column: 6, scope: !138)
!363 = !DILocation(line: 181, column: 7, scope: !364)
!364 = distinct !DILexicalBlock(scope: !365, file: !1, line: 181, column: 7)
!365 = distinct !DILexicalBlock(scope: !359, file: !1, line: 180, column: 20)
!366 = !DILocation(line: 181, column: 11, scope: !364)
!367 = !DILocation(line: 181, column: 7, scope: !365)
!368 = !DILocation(line: 182, column: 22, scope: !364)
!369 = !DILocation(line: 182, column: 25, scope: !364)
!370 = !DILocation(line: 182, column: 55, scope: !364)
!371 = !DILocation(line: 182, column: 4, scope: !372)
!372 = !DILexicalBlockFile(scope: !364, file: !1, discriminator: 1)
!373 = !DILocation(line: 182, column: 4, scope: !364)
!374 = !DILocation(line: 184, column: 22, scope: !364)
!375 = !DILocation(line: 184, column: 25, scope: !364)
!376 = !DILocation(line: 184, column: 55, scope: !364)
!377 = !DILocation(line: 184, column: 4, scope: !372)
!378 = !DILocation(line: 185, column: 3, scope: !365)
!379 = !DILocation(line: 188, column: 12, scope: !380)
!380 = distinct !DILexicalBlock(scope: !138, file: !1, line: 188, column: 6)
!381 = !DILocation(line: 188, column: 18, scope: !380)
!382 = !DILocation(line: 188, column: 6, scope: !380)
!383 = !DILocation(line: 188, column: 27, scope: !380)
!384 = !DILocation(line: 188, column: 6, scope: !138)
!385 = !DILocation(line: 189, column: 7, scope: !386)
!386 = distinct !DILexicalBlock(scope: !387, file: !1, line: 189, column: 7)
!387 = distinct !DILexicalBlock(scope: !380, file: !1, line: 188, column: 33)
!388 = !DILocation(line: 189, column: 11, scope: !386)
!389 = !DILocation(line: 189, column: 7, scope: !387)
!390 = !DILocation(line: 190, column: 22, scope: !386)
!391 = !DILocation(line: 190, column: 25, scope: !386)
!392 = !DILocation(line: 190, column: 54, scope: !386)
!393 = !DILocation(line: 190, column: 4, scope: !394)
!394 = !DILexicalBlockFile(scope: !386, file: !1, discriminator: 1)
!395 = !DILocation(line: 190, column: 4, scope: !386)
!396 = !DILocation(line: 192, column: 22, scope: !386)
!397 = !DILocation(line: 192, column: 25, scope: !386)
!398 = !DILocation(line: 192, column: 54, scope: !386)
!399 = !DILocation(line: 192, column: 4, scope: !394)
!400 = !DILocation(line: 193, column: 3, scope: !387)
!401 = !DILocation(line: 199, column: 44, scope: !402)
!402 = distinct !DILexicalBlock(scope: !138, file: !1, line: 199, column: 6)
!403 = !DILocation(line: 199, column: 6, scope: !402)
!404 = !DILocation(line: 199, column: 47, scope: !402)
!405 = !DILocation(line: 199, column: 6, scope: !138)
!406 = !DILocation(line: 200, column: 7, scope: !407)
!407 = distinct !DILexicalBlock(scope: !408, file: !1, line: 200, column: 7)
!408 = distinct !DILexicalBlock(scope: !402, file: !1, line: 199, column: 52)
!409 = !DILocation(line: 200, column: 27, scope: !407)
!410 = !DILocation(line: 200, column: 30, scope: !411)
!411 = !DILexicalBlockFile(scope: !407, file: !1, discriminator: 1)
!412 = !DILocation(line: 200, column: 50, scope: !411)
!413 = !DILocation(line: 201, column: 7, scope: !407)
!414 = !DILocation(line: 200, column: 7, scope: !415)
!415 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 2)
!416 = !DILocation(line: 203, column: 42, scope: !407)
!417 = !DILocation(line: 203, column: 4, scope: !407)
!418 = !DILocation(line: 206, column: 42, scope: !407)
!419 = !DILocation(line: 206, column: 4, scope: !407)
!420 = !DILocation(line: 207, column: 2, scope: !408)
!421 = !DILocation(line: 214, column: 6, scope: !422)
!422 = distinct !DILexicalBlock(scope: !138, file: !1, line: 214, column: 6)
!423 = !DILocation(line: 214, column: 6, scope: !138)
!424 = !DILocation(line: 215, column: 31, scope: !422)
!425 = !DILocation(line: 215, column: 37, scope: !422)
!426 = !DILocation(line: 215, column: 48, scope: !422)
!427 = !DILocation(line: 215, column: 3, scope: !422)
!428 = !DILocation(line: 217, column: 2, scope: !138)
!429 = !DILocation(line: 218, column: 1, scope: !138)
!430 = !DILocalVariable(name: "a", arg: 1, scope: !141, file: !1, line: 221, type: !44)
!431 = !DILocation(line: 221, column: 28, scope: !141)
!432 = !DILocalVariable(name: "client_data", arg: 2, scope: !141, file: !1, line: 221, type: !4)
!433 = !DILocation(line: 221, column: 37, scope: !141)
!434 = !DILocalVariable(name: "buff", arg: 3, scope: !141, file: !1, line: 221, type: !77)
!435 = !DILocation(line: 221, column: 62, scope: !141)
!436 = !DILocalVariable(name: "length", arg: 4, scope: !141, file: !1, line: 222, type: !21)
!437 = !DILocation(line: 222, column: 12, scope: !141)
!438 = !DILocalVariable(name: "mine", scope: !141, file: !1, line: 224, type: !5)
!439 = !DILocation(line: 224, column: 26, scope: !141)
!440 = !DILocalVariable(name: "bytesWritten", scope: !141, file: !1, line: 225, type: !72)
!441 = !DILocation(line: 225, column: 10, scope: !141)
!442 = !DILocation(line: 227, column: 35, scope: !141)
!443 = !DILocation(line: 227, column: 9, scope: !141)
!444 = !DILocation(line: 227, column: 7, scope: !141)
!445 = !DILocation(line: 228, column: 2, scope: !141)
!446 = !DILocation(line: 229, column: 24, scope: !447)
!447 = distinct !DILexicalBlock(scope: !448, file: !1, line: 228, column: 11)
!448 = distinct !DILexicalBlock(scope: !449, file: !1, line: 228, column: 2)
!449 = distinct !DILexicalBlock(scope: !141, file: !1, line: 228, column: 2)
!450 = !DILocation(line: 229, column: 30, scope: !447)
!451 = !DILocation(line: 229, column: 34, scope: !447)
!452 = !DILocation(line: 229, column: 40, scope: !447)
!453 = !DILocation(line: 229, column: 18, scope: !447)
!454 = !DILocation(line: 229, column: 16, scope: !447)
!455 = !DILocation(line: 230, column: 7, scope: !456)
!456 = distinct !DILexicalBlock(scope: !447, file: !1, line: 230, column: 7)
!457 = !DILocation(line: 230, column: 20, scope: !456)
!458 = !DILocation(line: 230, column: 7, scope: !447)
!459 = !DILocation(line: 231, column: 8, scope: !460)
!460 = distinct !DILexicalBlock(scope: !461, file: !1, line: 231, column: 8)
!461 = distinct !DILexicalBlock(scope: !456, file: !1, line: 230, column: 26)
!462 = !DILocation(line: 231, column: 14, scope: !460)
!463 = !DILocation(line: 231, column: 8, scope: !461)
!464 = !DILocation(line: 232, column: 5, scope: !460)
!465 = !DILocation(line: 233, column: 22, scope: !461)
!466 = !DILocation(line: 233, column: 25, scope: !461)
!467 = !DILocation(line: 233, column: 4, scope: !468)
!468 = !DILexicalBlockFile(scope: !461, file: !1, discriminator: 1)
!469 = !DILocation(line: 234, column: 4, scope: !461)
!470 = !DILocation(line: 236, column: 11, scope: !447)
!471 = !DILocation(line: 236, column: 3, scope: !447)
!472 = !DILocation(line: 238, column: 1, scope: !141)
!473 = !DILocalVariable(name: "a", arg: 1, scope: !144, file: !1, line: 241, type: !44)
!474 = !DILocation(line: 241, column: 28, scope: !144)
!475 = !DILocalVariable(name: "client_data", arg: 2, scope: !144, file: !1, line: 241, type: !4)
!476 = !DILocation(line: 241, column: 37, scope: !144)
!477 = !DILocalVariable(name: "mine", scope: !144, file: !1, line: 243, type: !5)
!478 = !DILocation(line: 243, column: 26, scope: !144)
!479 = !DILocation(line: 243, column: 59, scope: !144)
!480 = !DILocation(line: 243, column: 33, scope: !144)
!481 = !DILocation(line: 245, column: 8, scope: !144)
!482 = !DILocation(line: 247, column: 6, scope: !483)
!483 = distinct !DILexicalBlock(scope: !144, file: !1, line: 247, column: 6)
!484 = !DILocation(line: 247, column: 12, scope: !483)
!485 = !DILocation(line: 247, column: 15, scope: !483)
!486 = !DILocation(line: 247, column: 6, scope: !144)
!487 = !DILocation(line: 248, column: 9, scope: !483)
!488 = !DILocation(line: 248, column: 15, scope: !483)
!489 = !DILocation(line: 248, column: 3, scope: !483)
!490 = !DILocation(line: 250, column: 25, scope: !144)
!491 = !DILocation(line: 250, column: 31, scope: !144)
!492 = !DILocation(line: 250, column: 2, scope: !144)
!493 = !DILocation(line: 251, column: 7, scope: !144)
!494 = !DILocation(line: 251, column: 2, scope: !144)
!495 = !DILocation(line: 252, column: 2, scope: !144)
