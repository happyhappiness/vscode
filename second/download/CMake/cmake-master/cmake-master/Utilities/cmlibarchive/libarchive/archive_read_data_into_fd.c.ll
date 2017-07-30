; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_data_into_fd.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, {}*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }

@.str = private unnamed_addr constant [26 x i8] c"archive_read_data_into_fd\00", align 1
@.str.1 = private unnamed_addr constant [12 x i8] c"Write error\00", align 1
@.str.2 = private unnamed_addr constant [11 x i8] c"Seek error\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_data_into_fd(%struct.archive* %a, i32 %fd) #0 !dbg !11 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %fd.addr = alloca i32, align 4
  %st = alloca %struct.stat, align 8
  %r = alloca i32, align 4
  %r2 = alloca i32, align 4
  %buff = alloca i8*, align 8
  %size = alloca i64, align 8
  %bytes_to_write = alloca i64, align 8
  %bytes_written = alloca i64, align 8
  %target_offset = alloca i64, align 8
  %actual_offset = alloca i64, align 8
  %can_lseek = alloca i32, align 4
  %nulls = alloca i8*, align 8
  %nulls_size = alloca i64, align 8
  %magic_test = alloca i32, align 4
  %p = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !113, metadata !114), !dbg !115
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !116, metadata !114), !dbg !117
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !118, metadata !114), !dbg !156
  call void @llvm.dbg.declare(metadata i32* %r, metadata !157, metadata !114), !dbg !158
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !159, metadata !114), !dbg !160
  call void @llvm.dbg.declare(metadata i8** %buff, metadata !161, metadata !114), !dbg !162
  call void @llvm.dbg.declare(metadata i64* %size, metadata !163, metadata !114), !dbg !164
  call void @llvm.dbg.declare(metadata i64* %bytes_to_write, metadata !165, metadata !114), !dbg !166
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !167, metadata !114), !dbg !168
  call void @llvm.dbg.declare(metadata i64* %target_offset, metadata !169, metadata !114), !dbg !170
  call void @llvm.dbg.declare(metadata i64* %actual_offset, metadata !171, metadata !114), !dbg !172
  store i64 0, i64* %actual_offset, align 8, !dbg !172
  call void @llvm.dbg.declare(metadata i32* %can_lseek, metadata !173, metadata !114), !dbg !174
  call void @llvm.dbg.declare(metadata i8** %nulls, metadata !175, metadata !114), !dbg !176
  store i8* null, i8** %nulls, align 8, !dbg !176
  call void @llvm.dbg.declare(metadata i64* %nulls_size, metadata !177, metadata !114), !dbg !178
  store i64 16384, i64* %nulls_size, align 8, !dbg !178
  br label %do.body, !dbg !179

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !180, metadata !114), !dbg !182
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !183
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 14594245, i32 4, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str, i32 0, i32 0)), !dbg !183
  store i32 %call, i32* %magic_test, align 4, !dbg !183
  %1 = load i32, i32* %magic_test, align 4, !dbg !183
  %cmp = icmp eq i32 %1, -30, !dbg !183
  br i1 %cmp, label %if.then, label %if.end, !dbg !183

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !185
  br label %return, !dbg !185

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !188

do.end:                                           ; preds = %if.end
  %2 = load i32, i32* %fd.addr, align 4, !dbg !190
  %call1 = call i32 @fstat(i32 %2, %struct.stat* %st) #5, !dbg !191
  %cmp2 = icmp eq i32 %call1, 0, !dbg !192
  br i1 %cmp2, label %land.rhs, label %land.end, !dbg !193

land.rhs:                                         ; preds = %do.end
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !194
  %3 = load i32, i32* %st_mode, align 8, !dbg !194
  %and = and i32 %3, 61440, !dbg !194
  %cmp3 = icmp eq i32 %and, 32768, !dbg !194
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.end
  %4 = phi i1 [ false, %do.end ], [ %cmp3, %land.rhs ]
  %land.ext = zext i1 %4 to i32, !dbg !196
  store i32 %land.ext, i32* %can_lseek, align 4, !dbg !198
  %5 = load i32, i32* %can_lseek, align 4, !dbg !199
  %tobool = icmp ne i32 %5, 0, !dbg !199
  br i1 %tobool, label %if.end6, label %if.then4, !dbg !201

if.then4:                                         ; preds = %land.end
  %6 = load i64, i64* %nulls_size, align 8, !dbg !202
  %call5 = call noalias i8* @calloc(i64 1, i64 %6) #5, !dbg !203
  store i8* %call5, i8** %nulls, align 8, !dbg !204
  br label %if.end6, !dbg !205

if.end6:                                          ; preds = %if.then4, %land.end
  br label %while.cond, !dbg !206

while.cond:                                       ; preds = %while.end, %if.end6
  %7 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !207
  %call7 = call i32 @archive_read_data_block(%struct.archive* %7, i8** %buff, i64* %size, i64* %target_offset), !dbg !208
  store i32 %call7, i32* %r, align 4, !dbg !209
  %cmp8 = icmp eq i32 %call7, 0, !dbg !210
  br i1 %cmp8, label %while.body, label %while.end27, !dbg !211

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i8** %p, metadata !212, metadata !114), !dbg !214
  %8 = load i8*, i8** %buff, align 8, !dbg !215
  store i8* %8, i8** %p, align 8, !dbg !214
  %9 = load i64, i64* %target_offset, align 8, !dbg !216
  %10 = load i64, i64* %actual_offset, align 8, !dbg !218
  %cmp9 = icmp sgt i64 %9, %10, !dbg !219
  br i1 %cmp9, label %if.then10, label %if.end15, !dbg !220

if.then10:                                        ; preds = %while.body
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !221
  %12 = load i32, i32* %fd.addr, align 4, !dbg !223
  %13 = load i32, i32* %can_lseek, align 4, !dbg !224
  %14 = load i64, i64* %nulls_size, align 8, !dbg !225
  %15 = load i8*, i8** %nulls, align 8, !dbg !226
  %16 = load i64, i64* %target_offset, align 8, !dbg !227
  %17 = load i64, i64* %actual_offset, align 8, !dbg !228
  %call11 = call i32 @pad_to(%struct.archive* %11, i32 %12, i32 %13, i64 %14, i8* %15, i64 %16, i64 %17), !dbg !229
  store i32 %call11, i32* %r, align 4, !dbg !230
  %18 = load i32, i32* %r, align 4, !dbg !231
  %cmp12 = icmp ne i32 %18, 0, !dbg !233
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !234

if.then13:                                        ; preds = %if.then10
  br label %while.end27, !dbg !235

if.end14:                                         ; preds = %if.then10
  %19 = load i64, i64* %target_offset, align 8, !dbg !236
  store i64 %19, i64* %actual_offset, align 8, !dbg !237
  br label %if.end15, !dbg !238

if.end15:                                         ; preds = %if.end14, %while.body
  br label %while.cond16, !dbg !239

while.cond16:                                     ; preds = %if.end26, %if.end15
  %20 = load i64, i64* %size, align 8, !dbg !240
  %cmp17 = icmp ugt i64 %20, 0, !dbg !242
  br i1 %cmp17, label %while.body18, label %while.end, !dbg !243

while.body18:                                     ; preds = %while.cond16
  %21 = load i64, i64* %size, align 8, !dbg !244
  store i64 %21, i64* %bytes_to_write, align 8, !dbg !246
  %22 = load i64, i64* %bytes_to_write, align 8, !dbg !247
  %cmp19 = icmp ugt i64 %22, 1048576, !dbg !249
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !250

if.then20:                                        ; preds = %while.body18
  store i64 1048576, i64* %bytes_to_write, align 8, !dbg !251
  br label %if.end21, !dbg !252

if.end21:                                         ; preds = %if.then20, %while.body18
  %23 = load i32, i32* %fd.addr, align 4, !dbg !253
  %24 = load i8*, i8** %p, align 8, !dbg !254
  %25 = load i64, i64* %bytes_to_write, align 8, !dbg !255
  %call22 = call i64 @write(i32 %23, i8* %24, i64 %25), !dbg !256
  store i64 %call22, i64* %bytes_written, align 8, !dbg !257
  %26 = load i64, i64* %bytes_written, align 8, !dbg !258
  %cmp23 = icmp slt i64 %26, 0, !dbg !260
  br i1 %cmp23, label %if.then24, label %if.end26, !dbg !261

if.then24:                                        ; preds = %if.end21
  %27 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !262
  %call25 = call i32* @__errno_location() #1, !dbg !264
  %28 = load i32, i32* %call25, align 4, !dbg !264
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %27, i32 %28, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i32 0, i32 0)), !dbg !265
  store i32 -30, i32* %r, align 4, !dbg !267
  br label %cleanup, !dbg !268

if.end26:                                         ; preds = %if.end21
  %29 = load i64, i64* %bytes_written, align 8, !dbg !269
  %30 = load i64, i64* %actual_offset, align 8, !dbg !270
  %add = add nsw i64 %30, %29, !dbg !270
  store i64 %add, i64* %actual_offset, align 8, !dbg !270
  %31 = load i64, i64* %bytes_written, align 8, !dbg !271
  %32 = load i8*, i8** %p, align 8, !dbg !272
  %add.ptr = getelementptr inbounds i8, i8* %32, i64 %31, !dbg !272
  store i8* %add.ptr, i8** %p, align 8, !dbg !272
  %33 = load i64, i64* %bytes_written, align 8, !dbg !273
  %34 = load i64, i64* %size, align 8, !dbg !274
  %sub = sub i64 %34, %33, !dbg !274
  store i64 %sub, i64* %size, align 8, !dbg !274
  br label %while.cond16, !dbg !275

while.end:                                        ; preds = %while.cond16
  br label %while.cond, !dbg !277

while.end27:                                      ; preds = %if.then13, %while.cond
  %35 = load i32, i32* %r, align 4, !dbg !278
  %cmp28 = icmp eq i32 %35, 1, !dbg !280
  br i1 %cmp28, label %land.lhs.true, label %if.end35, !dbg !281

land.lhs.true:                                    ; preds = %while.end27
  %36 = load i64, i64* %target_offset, align 8, !dbg !282
  %37 = load i64, i64* %actual_offset, align 8, !dbg !284
  %cmp29 = icmp sgt i64 %36, %37, !dbg !285
  br i1 %cmp29, label %if.then30, label %if.end35, !dbg !286

if.then30:                                        ; preds = %land.lhs.true
  %38 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !287
  %39 = load i32, i32* %fd.addr, align 4, !dbg !289
  %40 = load i32, i32* %can_lseek, align 4, !dbg !290
  %41 = load i64, i64* %nulls_size, align 8, !dbg !291
  %42 = load i8*, i8** %nulls, align 8, !dbg !292
  %43 = load i64, i64* %target_offset, align 8, !dbg !293
  %44 = load i64, i64* %actual_offset, align 8, !dbg !294
  %call31 = call i32 @pad_to(%struct.archive* %38, i32 %39, i32 %40, i64 %41, i8* %42, i64 %43, i64 %44), !dbg !295
  store i32 %call31, i32* %r2, align 4, !dbg !296
  %45 = load i32, i32* %r2, align 4, !dbg !297
  %cmp32 = icmp ne i32 %45, 0, !dbg !299
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !300

if.then33:                                        ; preds = %if.then30
  %46 = load i32, i32* %r2, align 4, !dbg !301
  store i32 %46, i32* %r, align 4, !dbg !302
  br label %if.end34, !dbg !303

if.end34:                                         ; preds = %if.then33, %if.then30
  br label %if.end35, !dbg !304

if.end35:                                         ; preds = %if.end34, %land.lhs.true, %while.end27
  br label %cleanup, !dbg !305

cleanup:                                          ; preds = %if.end35, %if.then24
  %47 = load i8*, i8** %nulls, align 8, !dbg !307
  call void @free(i8* %47) #5, !dbg !308
  %48 = load i32, i32* %r, align 4, !dbg !309
  %cmp36 = icmp ne i32 %48, 1, !dbg !311
  br i1 %cmp36, label %if.then37, label %if.end38, !dbg !312

if.then37:                                        ; preds = %cleanup
  %49 = load i32, i32* %r, align 4, !dbg !313
  store i32 %49, i32* %retval, align 4, !dbg !314
  br label %return, !dbg !314

if.end38:                                         ; preds = %cleanup
  store i32 0, i32* %retval, align 4, !dbg !315
  br label %return, !dbg !315

return:                                           ; preds = %if.end38, %if.then37, %if.then
  %50 = load i32, i32* %retval, align 4, !dbg !316
  ret i32 %50, !dbg !316
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #3

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare i32 @archive_read_data_block(%struct.archive*, i8**, i64*, i64*) #2

; Function Attrs: nounwind uwtable
define internal i32 @pad_to(%struct.archive* %a, i32 %fd, i32 %can_lseek, i64 %nulls_size, i8* %nulls, i64 %target_offset, i64 %actual_offset) #0 !dbg !107 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %fd.addr = alloca i32, align 4
  %can_lseek.addr = alloca i32, align 4
  %nulls_size.addr = alloca i64, align 8
  %nulls.addr = alloca i8*, align 8
  %target_offset.addr = alloca i64, align 8
  %actual_offset.addr = alloca i64, align 8
  %to_write = alloca i64, align 8
  %bytes_written = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !317, metadata !114), !dbg !318
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !319, metadata !114), !dbg !320
  store i32 %can_lseek, i32* %can_lseek.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %can_lseek.addr, metadata !321, metadata !114), !dbg !322
  store i64 %nulls_size, i64* %nulls_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %nulls_size.addr, metadata !323, metadata !114), !dbg !324
  store i8* %nulls, i8** %nulls.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %nulls.addr, metadata !325, metadata !114), !dbg !326
  store i64 %target_offset, i64* %target_offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %target_offset.addr, metadata !327, metadata !114), !dbg !328
  store i64 %actual_offset, i64* %actual_offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %actual_offset.addr, metadata !329, metadata !114), !dbg !330
  call void @llvm.dbg.declare(metadata i64* %to_write, metadata !331, metadata !114), !dbg !332
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !333, metadata !114), !dbg !334
  %0 = load i32, i32* %can_lseek.addr, align 4, !dbg !335
  %tobool = icmp ne i32 %0, 0, !dbg !335
  br i1 %tobool, label %if.then, label %if.end3, !dbg !337

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %fd.addr, align 4, !dbg !338
  %2 = load i64, i64* %target_offset.addr, align 8, !dbg !340
  %3 = load i64, i64* %actual_offset.addr, align 8, !dbg !341
  %sub = sub nsw i64 %2, %3, !dbg !342
  %call = call i64 @lseek(i32 %1, i64 %sub, i32 1) #5, !dbg !343
  store i64 %call, i64* %actual_offset.addr, align 8, !dbg !344
  %4 = load i64, i64* %actual_offset.addr, align 8, !dbg !345
  %5 = load i64, i64* %target_offset.addr, align 8, !dbg !347
  %cmp = icmp ne i64 %4, %5, !dbg !348
  br i1 %cmp, label %if.then1, label %if.end, !dbg !349

if.then1:                                         ; preds = %if.then
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !350
  %call2 = call i32* @__errno_location() #1, !dbg !352
  %7 = load i32, i32* %call2, align 4, !dbg !352
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %6, i32 %7, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i32 0, i32 0)), !dbg !353
  store i32 -30, i32* %retval, align 4, !dbg !355
  br label %return, !dbg !355

if.end:                                           ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !356
  br label %return, !dbg !356

if.end3:                                          ; preds = %entry
  br label %while.cond, !dbg !357

while.cond:                                       ; preds = %if.end13, %if.end3
  %8 = load i64, i64* %target_offset.addr, align 8, !dbg !358
  %9 = load i64, i64* %actual_offset.addr, align 8, !dbg !360
  %cmp4 = icmp sgt i64 %8, %9, !dbg !361
  br i1 %cmp4, label %while.body, label %while.end, !dbg !362

while.body:                                       ; preds = %while.cond
  %10 = load i64, i64* %nulls_size.addr, align 8, !dbg !363
  store i64 %10, i64* %to_write, align 8, !dbg !365
  %11 = load i64, i64* %target_offset.addr, align 8, !dbg !366
  %12 = load i64, i64* %actual_offset.addr, align 8, !dbg !368
  %13 = load i64, i64* %nulls_size.addr, align 8, !dbg !369
  %add = add nsw i64 %12, %13, !dbg !370
  %cmp5 = icmp slt i64 %11, %add, !dbg !371
  br i1 %cmp5, label %if.then6, label %if.end8, !dbg !372

if.then6:                                         ; preds = %while.body
  %14 = load i64, i64* %target_offset.addr, align 8, !dbg !373
  %15 = load i64, i64* %actual_offset.addr, align 8, !dbg !374
  %sub7 = sub nsw i64 %14, %15, !dbg !375
  store i64 %sub7, i64* %to_write, align 8, !dbg !376
  br label %if.end8, !dbg !377

if.end8:                                          ; preds = %if.then6, %while.body
  %16 = load i32, i32* %fd.addr, align 4, !dbg !378
  %17 = load i8*, i8** %nulls.addr, align 8, !dbg !379
  %18 = load i64, i64* %to_write, align 8, !dbg !380
  %call9 = call i64 @write(i32 %16, i8* %17, i64 %18), !dbg !381
  store i64 %call9, i64* %bytes_written, align 8, !dbg !382
  %19 = load i64, i64* %bytes_written, align 8, !dbg !383
  %cmp10 = icmp slt i64 %19, 0, !dbg !385
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !386

if.then11:                                        ; preds = %if.end8
  %20 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !387
  %call12 = call i32* @__errno_location() #1, !dbg !389
  %21 = load i32, i32* %call12, align 4, !dbg !389
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %20, i32 %21, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i32 0, i32 0)), !dbg !390
  store i32 -30, i32* %retval, align 4, !dbg !392
  br label %return, !dbg !392

if.end13:                                         ; preds = %if.end8
  %22 = load i64, i64* %bytes_written, align 8, !dbg !393
  %23 = load i64, i64* %actual_offset.addr, align 8, !dbg !394
  %add14 = add nsw i64 %23, %22, !dbg !394
  store i64 %add14, i64* %actual_offset.addr, align 8, !dbg !394
  br label %while.cond, !dbg !395

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !397
  br label %return, !dbg !397

return:                                           ; preds = %while.end, %if.then11, %if.end, %if.then1
  %24 = load i32, i32* %retval, align 4, !dbg !398
  ret i32 %24, !dbg !398
}

declare i64 @write(i32, i8*, i64) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind
declare i64 @lseek(i32, i64, i32) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!110, !111}
!llvm.ident = !{!112}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !10)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_data_into_fd.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !7}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !5, line: 40, baseType: !6)
!5 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!6 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!7 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !8, line: 62, baseType: !9)
!8 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!9 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!10 = !{!11, !107}
!11 = distinct !DISubprogram(name: "archive_read_data_into_fd", scope: !1, file: !1, line: 81, type: !12, isLocal: false, isDefinition: true, scopeLine: 82, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!12 = !DISubroutineType(types: !13)
!13 = !{!14, !15, !14}
!14 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!16 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !17, line: 89, size: 1280, align: 64, elements: !18)
!17 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !{!19, !21, !22, !80, !81, !82, !83, !84, !85, !86, !87, !95, !96, !97, !98, !101, !102, !103, !104, !105, !106}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !16, file: !17, line: 96, baseType: !20, size: 32, align: 32)
!20 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !16, file: !17, line: 97, baseType: !20, size: 32, align: 32, offset: 32)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !16, file: !17, line: 103, baseType: !23, size: 64, align: 64, offset: 64)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !17, line: 63, size: 832, align: 64, elements: !25)
!25 = !{!26, !30, !31, !38, !39, !49, !53, !58, !59, !66, !67, !71, !73}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !24, file: !17, line: 64, baseType: !27, size: 64, align: 64)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!14, !15}
!30 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !24, file: !17, line: 65, baseType: !27, size: 64, align: 64, offset: 64)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !24, file: !17, line: 66, baseType: !32, size: 64, align: 64, offset: 128)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!33 = !DISubroutineType(types: !34)
!34 = !{!14, !15, !35}
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !37, line: 180, flags: DIFlagFwdDecl)
!37 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!38 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !24, file: !17, line: 68, baseType: !27, size: 64, align: 64, offset: 192)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !24, file: !17, line: 69, baseType: !40, size: 64, align: 64, offset: 256)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DISubroutineType(types: !42)
!42 = !{!43, !15, !47, !7}
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !44, line: 109, baseType: !45)
!44 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !46, line: 172, baseType: !6)
!46 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !24, file: !17, line: 71, baseType: !50, size: 64, align: 64, offset: 320)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DISubroutineType(types: !52)
!52 = !{!43, !15, !47, !7, !4}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !24, file: !17, line: 74, baseType: !54, size: 64, align: 64, offset: 384)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DISubroutineType(types: !56)
!56 = !{!14, !15, !57}
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !24, file: !17, line: 76, baseType: !32, size: 64, align: 64, offset: 448)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !24, file: !17, line: 78, baseType: !60, size: 64, align: 64, offset: 512)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DISubroutineType(types: !62)
!62 = !{!14, !15, !63, !64, !65}
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !24, file: !17, line: 81, baseType: !27, size: 64, align: 64, offset: 576)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !24, file: !17, line: 82, baseType: !68, size: 64, align: 64, offset: 640)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!69 = !DISubroutineType(types: !70)
!70 = !{!4, !15, !14}
!71 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !24, file: !17, line: 83, baseType: !72, size: 64, align: 64, offset: 704)
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !24, file: !17, line: 84, baseType: !74, size: 64, align: 64, offset: 768)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!77, !15, !14}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !79)
!79 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !16, file: !17, line: 105, baseType: !14, size: 32, align: 32, offset: 128)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !16, file: !17, line: 106, baseType: !77, size: 64, align: 64, offset: 192)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !16, file: !17, line: 108, baseType: !14, size: 32, align: 32, offset: 256)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !16, file: !17, line: 109, baseType: !77, size: 64, align: 64, offset: 320)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !16, file: !17, line: 112, baseType: !14, size: 32, align: 32, offset: 384)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !16, file: !17, line: 114, baseType: !14, size: 32, align: 32, offset: 416)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !16, file: !17, line: 115, baseType: !77, size: 64, align: 64, offset: 448)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !16, file: !17, line: 116, baseType: !88, size: 192, align: 64, offset: 512)
!88 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !89, line: 58, size: 192, align: 64, elements: !90)
!89 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!90 = !{!91, !93, !94}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !88, file: !89, line: 59, baseType: !92, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !88, file: !89, line: 60, baseType: !7, size: 64, align: 64, offset: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !88, file: !89, line: 61, baseType: !7, size: 64, align: 64, offset: 128)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !16, file: !17, line: 118, baseType: !92, size: 64, align: 64, offset: 704)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !16, file: !17, line: 119, baseType: !20, size: 32, align: 32, offset: 768)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !16, file: !17, line: 120, baseType: !20, size: 32, align: 32, offset: 800)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !16, file: !17, line: 121, baseType: !99, size: 64, align: 64, offset: 832)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !100, size: 64, align: 64)
!100 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !89, line: 70, flags: DIFlagFwdDecl)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !16, file: !17, line: 127, baseType: !77, size: 64, align: 64, offset: 896)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !16, file: !17, line: 128, baseType: !4, size: 64, align: 64, offset: 960)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !16, file: !17, line: 129, baseType: !4, size: 64, align: 64, offset: 1024)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !16, file: !17, line: 130, baseType: !7, size: 64, align: 64, offset: 1088)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !16, file: !17, line: 137, baseType: !79, size: 8, align: 8, offset: 1152)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !16, file: !17, line: 138, baseType: !7, size: 64, align: 64, offset: 1216)
!107 = distinct !DISubprogram(name: "pad_to", scope: !1, file: !1, line: 49, type: !108, isLocal: true, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!108 = !DISubroutineType(types: !109)
!109 = !{!14, !15, !14, !14, !7, !77, !4, !4}
!110 = !{i32 2, !"Dwarf Version", i32 4}
!111 = !{i32 2, !"Debug Info Version", i32 3}
!112 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!113 = !DILocalVariable(name: "a", arg: 1, scope: !11, file: !1, line: 81, type: !15)
!114 = !DIExpression()
!115 = !DILocation(line: 81, column: 43, scope: !11)
!116 = !DILocalVariable(name: "fd", arg: 2, scope: !11, file: !1, line: 81, type: !14)
!117 = !DILocation(line: 81, column: 50, scope: !11)
!118 = !DILocalVariable(name: "st", scope: !11, file: !1, line: 83, type: !119)
!119 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !120, line: 46, size: 1152, align: 64, elements: !121)
!120 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!121 = !{!122, !124, !126, !128, !130, !132, !134, !135, !136, !138, !140, !142, !150, !151, !152}
!122 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !119, file: !120, line: 48, baseType: !123, size: 64, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !46, line: 124, baseType: !9)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !119, file: !120, line: 53, baseType: !125, size: 64, align: 64, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !46, line: 127, baseType: !9)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !119, file: !120, line: 61, baseType: !127, size: 64, align: 64, offset: 128)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !46, line: 130, baseType: !9)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !119, file: !120, line: 62, baseType: !129, size: 32, align: 32, offset: 192)
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !46, line: 129, baseType: !20)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !119, file: !120, line: 64, baseType: !131, size: 32, align: 32, offset: 224)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !46, line: 125, baseType: !20)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !119, file: !120, line: 65, baseType: !133, size: 32, align: 32, offset: 256)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !46, line: 126, baseType: !20)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !119, file: !120, line: 67, baseType: !14, size: 32, align: 32, offset: 288)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !119, file: !120, line: 69, baseType: !123, size: 64, align: 64, offset: 320)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !119, file: !120, line: 74, baseType: !137, size: 64, align: 64, offset: 384)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !46, line: 131, baseType: !6)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !119, file: !120, line: 78, baseType: !139, size: 64, align: 64, offset: 448)
!139 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !46, line: 153, baseType: !6)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !119, file: !120, line: 80, baseType: !141, size: 64, align: 64, offset: 512)
!141 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !46, line: 158, baseType: !6)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !119, file: !120, line: 91, baseType: !143, size: 128, align: 64, offset: 576)
!143 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !144, line: 120, size: 128, align: 64, elements: !145)
!144 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!145 = !{!146, !148}
!146 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !143, file: !144, line: 122, baseType: !147, size: 64, align: 64)
!147 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !46, line: 139, baseType: !6)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !143, file: !144, line: 123, baseType: !149, size: 64, align: 64, offset: 64)
!149 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !46, line: 175, baseType: !6)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !119, file: !120, line: 92, baseType: !143, size: 128, align: 64, offset: 704)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !119, file: !120, line: 93, baseType: !143, size: 128, align: 64, offset: 832)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !119, file: !120, line: 106, baseType: !153, size: 192, align: 64, offset: 960)
!153 = !DICompositeType(tag: DW_TAG_array_type, baseType: !149, size: 192, align: 64, elements: !154)
!154 = !{!155}
!155 = !DISubrange(count: 3)
!156 = !DILocation(line: 83, column: 14, scope: !11)
!157 = !DILocalVariable(name: "r", scope: !11, file: !1, line: 84, type: !14)
!158 = !DILocation(line: 84, column: 6, scope: !11)
!159 = !DILocalVariable(name: "r2", scope: !11, file: !1, line: 84, type: !14)
!160 = !DILocation(line: 84, column: 9, scope: !11)
!161 = !DILocalVariable(name: "buff", scope: !11, file: !1, line: 85, type: !47)
!162 = !DILocation(line: 85, column: 14, scope: !11)
!163 = !DILocalVariable(name: "size", scope: !11, file: !1, line: 86, type: !7)
!164 = !DILocation(line: 86, column: 9, scope: !11)
!165 = !DILocalVariable(name: "bytes_to_write", scope: !11, file: !1, line: 86, type: !7)
!166 = !DILocation(line: 86, column: 15, scope: !11)
!167 = !DILocalVariable(name: "bytes_written", scope: !11, file: !1, line: 87, type: !43)
!168 = !DILocation(line: 87, column: 10, scope: !11)
!169 = !DILocalVariable(name: "target_offset", scope: !11, file: !1, line: 88, type: !4)
!170 = !DILocation(line: 88, column: 10, scope: !11)
!171 = !DILocalVariable(name: "actual_offset", scope: !11, file: !1, line: 89, type: !4)
!172 = !DILocation(line: 89, column: 10, scope: !11)
!173 = !DILocalVariable(name: "can_lseek", scope: !11, file: !1, line: 90, type: !14)
!174 = !DILocation(line: 90, column: 6, scope: !11)
!175 = !DILocalVariable(name: "nulls", scope: !11, file: !1, line: 91, type: !92)
!176 = !DILocation(line: 91, column: 8, scope: !11)
!177 = !DILocalVariable(name: "nulls_size", scope: !11, file: !1, line: 92, type: !7)
!178 = !DILocation(line: 92, column: 9, scope: !11)
!179 = !DILocation(line: 94, column: 2, scope: !11)
!180 = !DILocalVariable(name: "magic_test", scope: !181, file: !1, line: 94, type: !14)
!181 = distinct !DILexicalBlock(scope: !11, file: !1, line: 94, column: 2)
!182 = !DILocation(line: 94, column: 2, scope: !181)
!183 = !DILocation(line: 94, column: 2, scope: !184)
!184 = !DILexicalBlockFile(scope: !181, file: !1, discriminator: 1)
!185 = !DILocation(line: 94, column: 2, scope: !186)
!186 = !DILexicalBlockFile(scope: !187, file: !1, discriminator: 2)
!187 = distinct !DILexicalBlock(scope: !181, file: !1, line: 94, column: 2)
!188 = !DILocation(line: 94, column: 2, scope: !189)
!189 = !DILexicalBlockFile(scope: !181, file: !1, discriminator: 3)
!190 = !DILocation(line: 97, column: 21, scope: !11)
!191 = !DILocation(line: 97, column: 15, scope: !11)
!192 = !DILocation(line: 97, column: 30, scope: !11)
!193 = !DILocation(line: 97, column: 36, scope: !11)
!194 = !DILocation(line: 97, column: 39, scope: !195)
!195 = !DILexicalBlockFile(scope: !11, file: !1, discriminator: 1)
!196 = !DILocation(line: 97, column: 36, scope: !197)
!197 = !DILexicalBlockFile(scope: !11, file: !1, discriminator: 2)
!198 = !DILocation(line: 97, column: 12, scope: !197)
!199 = !DILocation(line: 98, column: 7, scope: !200)
!200 = distinct !DILexicalBlock(scope: !11, file: !1, line: 98, column: 6)
!201 = !DILocation(line: 98, column: 6, scope: !11)
!202 = !DILocation(line: 99, column: 21, scope: !200)
!203 = !DILocation(line: 99, column: 11, scope: !200)
!204 = !DILocation(line: 99, column: 9, scope: !200)
!205 = !DILocation(line: 99, column: 3, scope: !200)
!206 = !DILocation(line: 101, column: 2, scope: !11)
!207 = !DILocation(line: 101, column: 38, scope: !195)
!208 = !DILocation(line: 101, column: 14, scope: !195)
!209 = !DILocation(line: 101, column: 12, scope: !195)
!210 = !DILocation(line: 101, column: 72, scope: !195)
!211 = !DILocation(line: 101, column: 2, scope: !195)
!212 = !DILocalVariable(name: "p", scope: !213, file: !1, line: 103, type: !77)
!213 = distinct !DILexicalBlock(scope: !11, file: !1, line: 102, column: 18)
!214 = !DILocation(line: 103, column: 15, scope: !213)
!215 = !DILocation(line: 103, column: 19, scope: !213)
!216 = !DILocation(line: 104, column: 7, scope: !217)
!217 = distinct !DILexicalBlock(scope: !213, file: !1, line: 104, column: 7)
!218 = !DILocation(line: 104, column: 23, scope: !217)
!219 = !DILocation(line: 104, column: 21, scope: !217)
!220 = !DILocation(line: 104, column: 7, scope: !213)
!221 = !DILocation(line: 105, column: 15, scope: !222)
!222 = distinct !DILexicalBlock(scope: !217, file: !1, line: 104, column: 38)
!223 = !DILocation(line: 105, column: 18, scope: !222)
!224 = !DILocation(line: 105, column: 22, scope: !222)
!225 = !DILocation(line: 105, column: 33, scope: !222)
!226 = !DILocation(line: 105, column: 45, scope: !222)
!227 = !DILocation(line: 106, column: 8, scope: !222)
!228 = !DILocation(line: 106, column: 23, scope: !222)
!229 = !DILocation(line: 105, column: 8, scope: !222)
!230 = !DILocation(line: 105, column: 6, scope: !222)
!231 = !DILocation(line: 107, column: 8, scope: !232)
!232 = distinct !DILexicalBlock(scope: !222, file: !1, line: 107, column: 8)
!233 = !DILocation(line: 107, column: 10, scope: !232)
!234 = !DILocation(line: 107, column: 8, scope: !222)
!235 = !DILocation(line: 108, column: 5, scope: !232)
!236 = !DILocation(line: 109, column: 20, scope: !222)
!237 = !DILocation(line: 109, column: 18, scope: !222)
!238 = !DILocation(line: 110, column: 3, scope: !222)
!239 = !DILocation(line: 111, column: 3, scope: !213)
!240 = !DILocation(line: 111, column: 10, scope: !241)
!241 = !DILexicalBlockFile(scope: !213, file: !1, discriminator: 1)
!242 = !DILocation(line: 111, column: 15, scope: !241)
!243 = !DILocation(line: 111, column: 3, scope: !241)
!244 = !DILocation(line: 112, column: 21, scope: !245)
!245 = distinct !DILexicalBlock(scope: !213, file: !1, line: 111, column: 20)
!246 = !DILocation(line: 112, column: 19, scope: !245)
!247 = !DILocation(line: 113, column: 8, scope: !248)
!248 = distinct !DILexicalBlock(scope: !245, file: !1, line: 113, column: 8)
!249 = !DILocation(line: 113, column: 23, scope: !248)
!250 = !DILocation(line: 113, column: 8, scope: !245)
!251 = !DILocation(line: 114, column: 20, scope: !248)
!252 = !DILocation(line: 114, column: 5, scope: !248)
!253 = !DILocation(line: 115, column: 26, scope: !245)
!254 = !DILocation(line: 115, column: 30, scope: !245)
!255 = !DILocation(line: 115, column: 33, scope: !245)
!256 = !DILocation(line: 115, column: 20, scope: !245)
!257 = !DILocation(line: 115, column: 18, scope: !245)
!258 = !DILocation(line: 116, column: 8, scope: !259)
!259 = distinct !DILexicalBlock(scope: !245, file: !1, line: 116, column: 8)
!260 = !DILocation(line: 116, column: 22, scope: !259)
!261 = !DILocation(line: 116, column: 8, scope: !245)
!262 = !DILocation(line: 117, column: 23, scope: !263)
!263 = distinct !DILexicalBlock(scope: !259, file: !1, line: 116, column: 27)
!264 = !DILocation(line: 117, column: 26, scope: !263)
!265 = !DILocation(line: 117, column: 5, scope: !266)
!266 = !DILexicalBlockFile(scope: !263, file: !1, discriminator: 1)
!267 = !DILocation(line: 118, column: 7, scope: !263)
!268 = !DILocation(line: 119, column: 5, scope: !263)
!269 = !DILocation(line: 121, column: 21, scope: !245)
!270 = !DILocation(line: 121, column: 18, scope: !245)
!271 = !DILocation(line: 122, column: 9, scope: !245)
!272 = !DILocation(line: 122, column: 6, scope: !245)
!273 = !DILocation(line: 123, column: 12, scope: !245)
!274 = !DILocation(line: 123, column: 9, scope: !245)
!275 = !DILocation(line: 111, column: 3, scope: !276)
!276 = !DILexicalBlockFile(scope: !213, file: !1, discriminator: 2)
!277 = !DILocation(line: 101, column: 2, scope: !197)
!278 = !DILocation(line: 127, column: 6, scope: !279)
!279 = distinct !DILexicalBlock(scope: !11, file: !1, line: 127, column: 6)
!280 = !DILocation(line: 127, column: 8, scope: !279)
!281 = !DILocation(line: 127, column: 23, scope: !279)
!282 = !DILocation(line: 127, column: 26, scope: !283)
!283 = !DILexicalBlockFile(scope: !279, file: !1, discriminator: 1)
!284 = !DILocation(line: 127, column: 42, scope: !283)
!285 = !DILocation(line: 127, column: 40, scope: !283)
!286 = !DILocation(line: 127, column: 6, scope: !283)
!287 = !DILocation(line: 128, column: 15, scope: !288)
!288 = distinct !DILexicalBlock(scope: !279, file: !1, line: 127, column: 57)
!289 = !DILocation(line: 128, column: 18, scope: !288)
!290 = !DILocation(line: 128, column: 22, scope: !288)
!291 = !DILocation(line: 128, column: 33, scope: !288)
!292 = !DILocation(line: 128, column: 45, scope: !288)
!293 = !DILocation(line: 129, column: 7, scope: !288)
!294 = !DILocation(line: 129, column: 22, scope: !288)
!295 = !DILocation(line: 128, column: 8, scope: !288)
!296 = !DILocation(line: 128, column: 6, scope: !288)
!297 = !DILocation(line: 130, column: 7, scope: !298)
!298 = distinct !DILexicalBlock(scope: !288, file: !1, line: 130, column: 7)
!299 = !DILocation(line: 130, column: 10, scope: !298)
!300 = !DILocation(line: 130, column: 7, scope: !288)
!301 = !DILocation(line: 131, column: 8, scope: !298)
!302 = !DILocation(line: 131, column: 6, scope: !298)
!303 = !DILocation(line: 131, column: 4, scope: !298)
!304 = !DILocation(line: 132, column: 2, scope: !288)
!305 = !DILocation(line: 127, column: 42, scope: !306)
!306 = !DILexicalBlockFile(scope: !279, file: !1, discriminator: 2)
!307 = !DILocation(line: 135, column: 7, scope: !11)
!308 = !DILocation(line: 135, column: 2, scope: !11)
!309 = !DILocation(line: 136, column: 6, scope: !310)
!310 = distinct !DILexicalBlock(scope: !11, file: !1, line: 136, column: 6)
!311 = !DILocation(line: 136, column: 8, scope: !310)
!312 = !DILocation(line: 136, column: 6, scope: !11)
!313 = !DILocation(line: 137, column: 11, scope: !310)
!314 = !DILocation(line: 137, column: 3, scope: !310)
!315 = !DILocation(line: 138, column: 2, scope: !11)
!316 = !DILocation(line: 139, column: 1, scope: !11)
!317 = !DILocalVariable(name: "a", arg: 1, scope: !107, file: !1, line: 49, type: !15)
!318 = !DILocation(line: 49, column: 24, scope: !107)
!319 = !DILocalVariable(name: "fd", arg: 2, scope: !107, file: !1, line: 49, type: !14)
!320 = !DILocation(line: 49, column: 31, scope: !107)
!321 = !DILocalVariable(name: "can_lseek", arg: 3, scope: !107, file: !1, line: 49, type: !14)
!322 = !DILocation(line: 49, column: 39, scope: !107)
!323 = !DILocalVariable(name: "nulls_size", arg: 4, scope: !107, file: !1, line: 50, type: !7)
!324 = !DILocation(line: 50, column: 12, scope: !107)
!325 = !DILocalVariable(name: "nulls", arg: 5, scope: !107, file: !1, line: 50, type: !77)
!326 = !DILocation(line: 50, column: 36, scope: !107)
!327 = !DILocalVariable(name: "target_offset", arg: 6, scope: !107, file: !1, line: 51, type: !4)
!328 = !DILocation(line: 51, column: 13, scope: !107)
!329 = !DILocalVariable(name: "actual_offset", arg: 7, scope: !107, file: !1, line: 51, type: !4)
!330 = !DILocation(line: 51, column: 36, scope: !107)
!331 = !DILocalVariable(name: "to_write", scope: !107, file: !1, line: 53, type: !7)
!332 = !DILocation(line: 53, column: 9, scope: !107)
!333 = !DILocalVariable(name: "bytes_written", scope: !107, file: !1, line: 54, type: !43)
!334 = !DILocation(line: 54, column: 10, scope: !107)
!335 = !DILocation(line: 56, column: 6, scope: !336)
!336 = distinct !DILexicalBlock(scope: !107, file: !1, line: 56, column: 6)
!337 = !DILocation(line: 56, column: 6, scope: !107)
!338 = !DILocation(line: 57, column: 25, scope: !339)
!339 = distinct !DILexicalBlock(scope: !336, file: !1, line: 56, column: 17)
!340 = !DILocation(line: 58, column: 7, scope: !339)
!341 = !DILocation(line: 58, column: 23, scope: !339)
!342 = !DILocation(line: 58, column: 21, scope: !339)
!343 = !DILocation(line: 57, column: 19, scope: !339)
!344 = !DILocation(line: 57, column: 17, scope: !339)
!345 = !DILocation(line: 59, column: 7, scope: !346)
!346 = distinct !DILexicalBlock(scope: !339, file: !1, line: 59, column: 7)
!347 = !DILocation(line: 59, column: 24, scope: !346)
!348 = !DILocation(line: 59, column: 21, scope: !346)
!349 = !DILocation(line: 59, column: 7, scope: !339)
!350 = !DILocation(line: 60, column: 22, scope: !351)
!351 = distinct !DILexicalBlock(scope: !346, file: !1, line: 59, column: 39)
!352 = !DILocation(line: 60, column: 25, scope: !351)
!353 = !DILocation(line: 60, column: 4, scope: !354)
!354 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 1)
!355 = !DILocation(line: 61, column: 4, scope: !351)
!356 = !DILocation(line: 63, column: 3, scope: !339)
!357 = !DILocation(line: 65, column: 2, scope: !107)
!358 = !DILocation(line: 65, column: 9, scope: !359)
!359 = !DILexicalBlockFile(scope: !107, file: !1, discriminator: 1)
!360 = !DILocation(line: 65, column: 25, scope: !359)
!361 = !DILocation(line: 65, column: 23, scope: !359)
!362 = !DILocation(line: 65, column: 2, scope: !359)
!363 = !DILocation(line: 66, column: 14, scope: !364)
!364 = distinct !DILexicalBlock(scope: !107, file: !1, line: 65, column: 40)
!365 = !DILocation(line: 66, column: 12, scope: !364)
!366 = !DILocation(line: 67, column: 7, scope: !367)
!367 = distinct !DILexicalBlock(scope: !364, file: !1, line: 67, column: 7)
!368 = !DILocation(line: 67, column: 23, scope: !367)
!369 = !DILocation(line: 67, column: 48, scope: !367)
!370 = !DILocation(line: 67, column: 37, scope: !367)
!371 = !DILocation(line: 67, column: 21, scope: !367)
!372 = !DILocation(line: 67, column: 7, scope: !364)
!373 = !DILocation(line: 68, column: 24, scope: !367)
!374 = !DILocation(line: 68, column: 40, scope: !367)
!375 = !DILocation(line: 68, column: 38, scope: !367)
!376 = !DILocation(line: 68, column: 13, scope: !367)
!377 = !DILocation(line: 68, column: 4, scope: !367)
!378 = !DILocation(line: 69, column: 25, scope: !364)
!379 = !DILocation(line: 69, column: 29, scope: !364)
!380 = !DILocation(line: 69, column: 36, scope: !364)
!381 = !DILocation(line: 69, column: 19, scope: !364)
!382 = !DILocation(line: 69, column: 17, scope: !364)
!383 = !DILocation(line: 70, column: 7, scope: !384)
!384 = distinct !DILexicalBlock(scope: !364, file: !1, line: 70, column: 7)
!385 = !DILocation(line: 70, column: 21, scope: !384)
!386 = !DILocation(line: 70, column: 7, scope: !364)
!387 = !DILocation(line: 71, column: 22, scope: !388)
!388 = distinct !DILexicalBlock(scope: !384, file: !1, line: 70, column: 26)
!389 = !DILocation(line: 71, column: 25, scope: !388)
!390 = !DILocation(line: 71, column: 4, scope: !391)
!391 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 1)
!392 = !DILocation(line: 72, column: 4, scope: !388)
!393 = !DILocation(line: 74, column: 20, scope: !364)
!394 = !DILocation(line: 74, column: 17, scope: !364)
!395 = !DILocation(line: 65, column: 2, scope: !396)
!396 = !DILexicalBlockFile(scope: !107, file: !1, discriminator: 2)
!397 = !DILocation(line: 76, column: 2, scope: !107)
!398 = !DILocation(line: 77, column: 1, scope: !107)
