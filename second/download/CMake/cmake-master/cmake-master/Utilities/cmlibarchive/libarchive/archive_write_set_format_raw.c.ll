; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_raw.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.raw = type { i32 }

@.str = private unnamed_addr constant [29 x i8] c"archive_write_set_format_raw\00", align 1
@.str.1 = private unnamed_addr constant [24 x i8] c"Can't allocate raw data\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"raw\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"RAW\00", align 1
@.str.4 = private unnamed_addr constant [43 x i8] c"Raw format only supports filetype AE_IFREG\00", align 1
@.str.5 = private unnamed_addr constant [47 x i8] c"Raw format only supports one entry per archive\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_raw(%struct.archive* %_a) #0 !dbg !199 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %raw = alloca %struct.raw*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !206, metadata !207), !dbg !208
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !209, metadata !207), !dbg !210
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !211
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !212
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !210
  call void @llvm.dbg.declare(metadata %struct.raw** %raw, metadata !213, metadata !207), !dbg !214
  br label %do.body, !dbg !215

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !216, metadata !207), !dbg !218
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !219
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str, i32 0, i32 0)), !dbg !219
  store i32 %call, i32* %magic_test, align 4, !dbg !219
  %3 = load i32, i32* %magic_test, align 4, !dbg !219
  %cmp = icmp eq i32 %3, -30, !dbg !219
  br i1 %cmp, label %if.then, label %if.end, !dbg !219

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !221
  br label %return, !dbg !221

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !224

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !226
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !228
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !228
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !229
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !230

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !231
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !232
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !232
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !233
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !234
  br label %if.end5, !dbg !234

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 4) #4, !dbg !235
  %9 = bitcast i8* %call6 to %struct.raw*, !dbg !236
  store %struct.raw* %9, %struct.raw** %raw, align 8, !dbg !237
  %10 = load %struct.raw*, %struct.raw** %raw, align 8, !dbg !238
  %cmp7 = icmp eq %struct.raw* %10, null, !dbg !240
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !241

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !242
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !244
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.1, i32 0, i32 0)), !dbg !245
  store i32 -30, i32* %retval, align 4, !dbg !246
  br label %return, !dbg !246

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.raw*, %struct.raw** %raw, align 8, !dbg !247
  %entries_written = getelementptr inbounds %struct.raw, %struct.raw* %12, i32 0, i32 0, !dbg !248
  store i32 0, i32* %entries_written, align 4, !dbg !249
  %13 = load %struct.raw*, %struct.raw** %raw, align 8, !dbg !250
  %14 = bitcast %struct.raw* %13 to i8*, !dbg !250
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !251
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 14, !dbg !252
  store i8* %14, i8** %format_data, align 8, !dbg !253
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !254
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 15, !dbg !255
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8** %format_name, align 8, !dbg !256
  %17 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !257
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 17, !dbg !258
  store i32 (%struct.archive_write*, i8*, i8*)* null, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !259
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !260
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 19, !dbg !261
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_raw_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !262
  %19 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !263
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 20, !dbg !264
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_raw_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !265
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !266
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 18, !dbg !267
  store i32 (%struct.archive_write*)* null, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !268
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !269
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 21, !dbg !270
  store i32 (%struct.archive_write*)* null, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !271
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !272
  %format_free10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 22, !dbg !273
  store i32 (%struct.archive_write*)* @archive_write_raw_free, i32 (%struct.archive_write*)** %format_free10, align 8, !dbg !274
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !275
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 0, !dbg !276
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 3, !dbg !277
  store i32 589824, i32* %archive_format, align 8, !dbg !278
  %24 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !279
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 0, !dbg !280
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 4, !dbg !281
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !282
  store i32 0, i32* %retval, align 4, !dbg !283
  br label %return, !dbg !283

return:                                           ; preds = %if.end9, %if.then8, %if.then
  %25 = load i32, i32* %retval, align 4, !dbg !284
  ret i32 %25, !dbg !284
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_raw_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !200 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %raw = alloca %struct.raw*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !285, metadata !207), !dbg !286
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !287, metadata !207), !dbg !288
  call void @llvm.dbg.declare(metadata %struct.raw** %raw, metadata !289, metadata !207), !dbg !290
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !291
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !292
  %1 = load i8*, i8** %format_data, align 8, !dbg !292
  %2 = bitcast i8* %1 to %struct.raw*, !dbg !293
  store %struct.raw* %2, %struct.raw** %raw, align 8, !dbg !290
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !294
  %call = call i32 @archive_entry_filetype(%struct.archive_entry* %3), !dbg !296
  %cmp = icmp ne i32 %call, 32768, !dbg !297
  br i1 %cmp, label %if.then, label %if.end, !dbg !298

if.then:                                          ; preds = %entry
  %4 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !299
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !301
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 34, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.4, i32 0, i32 0)), !dbg !302
  store i32 -30, i32* %retval, align 4, !dbg !303
  br label %return, !dbg !303

if.end:                                           ; preds = %entry
  %5 = load %struct.raw*, %struct.raw** %raw, align 8, !dbg !304
  %entries_written = getelementptr inbounds %struct.raw, %struct.raw* %5, i32 0, i32 0, !dbg !306
  %6 = load i32, i32* %entries_written, align 4, !dbg !306
  %cmp2 = icmp sgt i32 %6, 0, !dbg !307
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !308

if.then3:                                         ; preds = %if.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !309
  %archive4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !311
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive4, i32 34, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.5, i32 0, i32 0)), !dbg !312
  store i32 -30, i32* %retval, align 4, !dbg !313
  br label %return, !dbg !313

if.end5:                                          ; preds = %if.end
  %8 = load %struct.raw*, %struct.raw** %raw, align 8, !dbg !314
  %entries_written6 = getelementptr inbounds %struct.raw, %struct.raw* %8, i32 0, i32 0, !dbg !315
  %9 = load i32, i32* %entries_written6, align 4, !dbg !316
  %inc = add nsw i32 %9, 1, !dbg !316
  store i32 %inc, i32* %entries_written6, align 4, !dbg !316
  store i32 0, i32* %retval, align 4, !dbg !317
  br label %return, !dbg !317

return:                                           ; preds = %if.end5, %if.then3, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !318
  ret i32 %10, !dbg !318
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_raw_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !201 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !319, metadata !207), !dbg !320
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !321, metadata !207), !dbg !322
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !323, metadata !207), !dbg !324
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !325, metadata !207), !dbg !326
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !327
  %1 = load i8*, i8** %buff.addr, align 8, !dbg !328
  %2 = load i64, i64* %s.addr, align 8, !dbg !329
  %call = call i32 @__archive_write_output(%struct.archive_write* %0, i8* %1, i64 %2), !dbg !330
  store i32 %call, i32* %ret, align 4, !dbg !331
  %3 = load i32, i32* %ret, align 4, !dbg !332
  %cmp = icmp sge i32 %3, 0, !dbg !334
  br i1 %cmp, label %if.then, label %if.else, !dbg !335

if.then:                                          ; preds = %entry
  %4 = load i64, i64* %s.addr, align 8, !dbg !336
  store i64 %4, i64* %retval, align 8, !dbg !337
  br label %return, !dbg !337

if.else:                                          ; preds = %entry
  %5 = load i32, i32* %ret, align 4, !dbg !338
  %conv = sext i32 %5 to i64, !dbg !339
  store i64 %conv, i64* %retval, align 8, !dbg !340
  br label %return, !dbg !340

return:                                           ; preds = %if.else, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !341
  ret i64 %6, !dbg !341
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_raw_free(%struct.archive_write* %a) #0 !dbg !202 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %raw = alloca %struct.raw*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !342, metadata !207), !dbg !343
  call void @llvm.dbg.declare(metadata %struct.raw** %raw, metadata !344, metadata !207), !dbg !345
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !346
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !347
  %1 = load i8*, i8** %format_data, align 8, !dbg !347
  %2 = bitcast i8* %1 to %struct.raw*, !dbg !348
  store %struct.raw* %2, %struct.raw** %raw, align 8, !dbg !349
  %3 = load %struct.raw*, %struct.raw** %raw, align 8, !dbg !350
  %4 = bitcast %struct.raw* %3 to i8*, !dbg !350
  call void @free(i8* %4) #4, !dbg !351
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !352
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 14, !dbg !353
  store i8* null, i8** %format_data1, align 8, !dbg !354
  ret i32 0, !dbg !355
}

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!203, !204}
!llvm.ident = !{!205}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !198)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_raw.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !124, !192, !196}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !117, !118, !125, !131, !134, !135, !136, !137, !163, !164, !165, !166, !170, !174, !175, !179, !183, !184, !185, !186, !191}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 153, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 109, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !114, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !116)
!116 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !119, size: 64, align: 64, offset: 1600)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !121, line: 241, baseType: !122)
!121 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!122 = !DISubroutineType(types: !123)
!123 = !{!23, !24, !124}
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !126, size: 64, align: 64, offset: 1664)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !121, line: 237, baseType: !128)
!128 = !DISubroutineType(types: !129)
!129 = !{!130, !24, !124, !43, !45}
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 86, baseType: !38)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !132, size: 64, align: 64, offset: 1728)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !121, line: 243, baseType: !122)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !124, size: 64, align: 64, offset: 1792)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !138, size: 64, align: 64, offset: 1920)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !140)
!140 = !{!141, !142, !143, !144, !148, !152, !156, !157, !158, !159, !160, !161, !162}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !139, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !139, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !139, file: !6, line: 46, baseType: !138, size: 64, align: 64, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !139, file: !6, line: 47, baseType: !145, size: 64, align: 64, offset: 192)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DISubroutineType(types: !147)
!147 = !{!23, !138, !80, !80}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !139, file: !6, line: 49, baseType: !149, size: 64, align: 64, offset: 256)
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !150, size: 64, align: 64)
!150 = !DISubroutineType(types: !151)
!151 = !{!23, !138}
!152 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !139, file: !6, line: 50, baseType: !153, size: 64, align: 64, offset: 320)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DISubroutineType(types: !155)
!155 = !{!23, !138, !43, !45}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !139, file: !6, line: 51, baseType: !149, size: 64, align: 64, offset: 384)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !139, file: !6, line: 52, baseType: !149, size: 64, align: 64, offset: 448)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !139, file: !6, line: 53, baseType: !124, size: 64, align: 64, offset: 512)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !139, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !139, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !139, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !139, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !138, size: 64, align: 64, offset: 1984)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !124, size: 64, align: 64, offset: 2048)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !167, size: 64, align: 64, offset: 2176)
!167 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!168 = !DISubroutineType(types: !169)
!169 = !{!23, !4}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !171, size: 64, align: 64, offset: 2240)
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !172, size: 64, align: 64)
!172 = !DISubroutineType(types: !173)
!173 = !{!23, !4, !80, !80}
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !167, size: 64, align: 64, offset: 2304)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !176, size: 64, align: 64, offset: 2368)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DISubroutineType(types: !178)
!178 = !{!23, !4, !30}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !180, size: 64, align: 64, offset: 2432)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!181 = !DISubroutineType(types: !182)
!182 = !{!38, !4, !43, !45}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !167, size: 64, align: 64, offset: 2496)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !167, size: 64, align: 64, offset: 2560)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !187, size: 64, align: 64, offset: 2688)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !121, line: 256, baseType: !189)
!189 = !DISubroutineType(types: !190)
!190 = !{!80, !24, !124}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !124, size: 64, align: 64, offset: 2752)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "raw", file: !1, line: 41, size: 32, align: 32, elements: !194)
!194 = !{!195}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "entries_written", scope: !193, file: !1, line: 42, baseType: !23, size: 32, align: 32)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !39, line: 70, baseType: !197)
!197 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!198 = !{!199, !200, !201, !202}
!199 = distinct !DISubprogram(name: "archive_write_set_format_raw", scope: !1, file: !1, line: 49, type: !21, isLocal: false, isDefinition: true, scopeLine: 50, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!200 = distinct !DISubprogram(name: "archive_write_raw_header", scope: !1, file: !1, line: 83, type: !177, isLocal: true, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!201 = distinct !DISubprogram(name: "archive_write_raw_data", scope: !1, file: !1, line: 105, type: !181, isLocal: true, isDefinition: true, scopeLine: 106, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!202 = distinct !DISubprogram(name: "archive_write_raw_free", scope: !1, file: !1, line: 117, type: !168, isLocal: true, isDefinition: true, scopeLine: 118, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!203 = !{i32 2, !"Dwarf Version", i32 4}
!204 = !{i32 2, !"Debug Info Version", i32 3}
!205 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!206 = !DILocalVariable(name: "_a", arg: 1, scope: !199, file: !1, line: 49, type: !24)
!207 = !DIExpression()
!208 = !DILocation(line: 49, column: 46, scope: !199)
!209 = !DILocalVariable(name: "a", scope: !199, file: !1, line: 51, type: !4)
!210 = !DILocation(line: 51, column: 24, scope: !199)
!211 = !DILocation(line: 51, column: 52, scope: !199)
!212 = !DILocation(line: 51, column: 28, scope: !199)
!213 = !DILocalVariable(name: "raw", scope: !199, file: !1, line: 52, type: !192)
!214 = !DILocation(line: 52, column: 14, scope: !199)
!215 = !DILocation(line: 54, column: 2, scope: !199)
!216 = !DILocalVariable(name: "magic_test", scope: !217, file: !1, line: 54, type: !23)
!217 = distinct !DILexicalBlock(scope: !199, file: !1, line: 54, column: 2)
!218 = !DILocation(line: 54, column: 2, scope: !217)
!219 = !DILocation(line: 54, column: 2, scope: !220)
!220 = !DILexicalBlockFile(scope: !217, file: !1, discriminator: 1)
!221 = !DILocation(line: 54, column: 2, scope: !222)
!222 = !DILexicalBlockFile(scope: !223, file: !1, discriminator: 2)
!223 = distinct !DILexicalBlock(scope: !217, file: !1, line: 54, column: 2)
!224 = !DILocation(line: 54, column: 2, scope: !225)
!225 = !DILexicalBlockFile(scope: !217, file: !1, discriminator: 3)
!226 = !DILocation(line: 58, column: 6, scope: !227)
!227 = distinct !DILexicalBlock(scope: !199, file: !1, line: 58, column: 6)
!228 = !DILocation(line: 58, column: 9, scope: !227)
!229 = !DILocation(line: 58, column: 21, scope: !227)
!230 = !DILocation(line: 58, column: 6, scope: !199)
!231 = !DILocation(line: 59, column: 4, scope: !227)
!232 = !DILocation(line: 59, column: 7, scope: !227)
!233 = !DILocation(line: 59, column: 20, scope: !227)
!234 = !DILocation(line: 59, column: 3, scope: !227)
!235 = !DILocation(line: 61, column: 22, scope: !199)
!236 = !DILocation(line: 61, column: 8, scope: !199)
!237 = !DILocation(line: 61, column: 6, scope: !199)
!238 = !DILocation(line: 62, column: 6, scope: !239)
!239 = distinct !DILexicalBlock(scope: !199, file: !1, line: 62, column: 6)
!240 = !DILocation(line: 62, column: 10, scope: !239)
!241 = !DILocation(line: 62, column: 6, scope: !199)
!242 = !DILocation(line: 63, column: 22, scope: !243)
!243 = distinct !DILexicalBlock(scope: !239, file: !1, line: 62, column: 19)
!244 = !DILocation(line: 63, column: 25, scope: !243)
!245 = !DILocation(line: 63, column: 3, scope: !243)
!246 = !DILocation(line: 64, column: 3, scope: !243)
!247 = !DILocation(line: 66, column: 2, scope: !199)
!248 = !DILocation(line: 66, column: 7, scope: !199)
!249 = !DILocation(line: 66, column: 23, scope: !199)
!250 = !DILocation(line: 67, column: 19, scope: !199)
!251 = !DILocation(line: 67, column: 2, scope: !199)
!252 = !DILocation(line: 67, column: 5, scope: !199)
!253 = !DILocation(line: 67, column: 17, scope: !199)
!254 = !DILocation(line: 68, column: 2, scope: !199)
!255 = !DILocation(line: 68, column: 5, scope: !199)
!256 = !DILocation(line: 68, column: 17, scope: !199)
!257 = !DILocation(line: 70, column: 2, scope: !199)
!258 = !DILocation(line: 70, column: 5, scope: !199)
!259 = !DILocation(line: 70, column: 20, scope: !199)
!260 = !DILocation(line: 71, column: 2, scope: !199)
!261 = !DILocation(line: 71, column: 5, scope: !199)
!262 = !DILocation(line: 71, column: 25, scope: !199)
!263 = !DILocation(line: 72, column: 2, scope: !199)
!264 = !DILocation(line: 72, column: 5, scope: !199)
!265 = !DILocation(line: 72, column: 23, scope: !199)
!266 = !DILocation(line: 73, column: 2, scope: !199)
!267 = !DILocation(line: 73, column: 5, scope: !199)
!268 = !DILocation(line: 73, column: 25, scope: !199)
!269 = !DILocation(line: 75, column: 2, scope: !199)
!270 = !DILocation(line: 75, column: 5, scope: !199)
!271 = !DILocation(line: 75, column: 18, scope: !199)
!272 = !DILocation(line: 76, column: 2, scope: !199)
!273 = !DILocation(line: 76, column: 5, scope: !199)
!274 = !DILocation(line: 76, column: 17, scope: !199)
!275 = !DILocation(line: 77, column: 2, scope: !199)
!276 = !DILocation(line: 77, column: 5, scope: !199)
!277 = !DILocation(line: 77, column: 13, scope: !199)
!278 = !DILocation(line: 77, column: 28, scope: !199)
!279 = !DILocation(line: 78, column: 2, scope: !199)
!280 = !DILocation(line: 78, column: 5, scope: !199)
!281 = !DILocation(line: 78, column: 13, scope: !199)
!282 = !DILocation(line: 78, column: 33, scope: !199)
!283 = !DILocation(line: 79, column: 2, scope: !199)
!284 = !DILocation(line: 80, column: 1, scope: !199)
!285 = !DILocalVariable(name: "a", arg: 1, scope: !200, file: !1, line: 83, type: !4)
!286 = !DILocation(line: 83, column: 48, scope: !200)
!287 = !DILocalVariable(name: "entry", arg: 2, scope: !200, file: !1, line: 83, type: !30)
!288 = !DILocation(line: 83, column: 73, scope: !200)
!289 = !DILocalVariable(name: "raw", scope: !200, file: !1, line: 85, type: !192)
!290 = !DILocation(line: 85, column: 14, scope: !200)
!291 = !DILocation(line: 85, column: 34, scope: !200)
!292 = !DILocation(line: 85, column: 37, scope: !200)
!293 = !DILocation(line: 85, column: 20, scope: !200)
!294 = !DILocation(line: 87, column: 29, scope: !295)
!295 = distinct !DILexicalBlock(scope: !200, file: !1, line: 87, column: 6)
!296 = !DILocation(line: 87, column: 6, scope: !295)
!297 = !DILocation(line: 87, column: 36, scope: !295)
!298 = !DILocation(line: 87, column: 6, scope: !200)
!299 = !DILocation(line: 88, column: 22, scope: !300)
!300 = distinct !DILexicalBlock(scope: !295, file: !1, line: 87, column: 49)
!301 = !DILocation(line: 88, column: 25, scope: !300)
!302 = !DILocation(line: 88, column: 3, scope: !300)
!303 = !DILocation(line: 90, column: 3, scope: !300)
!304 = !DILocation(line: 94, column: 6, scope: !305)
!305 = distinct !DILexicalBlock(scope: !200, file: !1, line: 94, column: 6)
!306 = !DILocation(line: 94, column: 11, scope: !305)
!307 = !DILocation(line: 94, column: 27, scope: !305)
!308 = !DILocation(line: 94, column: 6, scope: !200)
!309 = !DILocation(line: 95, column: 22, scope: !310)
!310 = distinct !DILexicalBlock(scope: !305, file: !1, line: 94, column: 32)
!311 = !DILocation(line: 95, column: 25, scope: !310)
!312 = !DILocation(line: 95, column: 3, scope: !310)
!313 = !DILocation(line: 97, column: 3, scope: !310)
!314 = !DILocation(line: 99, column: 2, scope: !200)
!315 = !DILocation(line: 99, column: 7, scope: !200)
!316 = !DILocation(line: 99, column: 22, scope: !200)
!317 = !DILocation(line: 101, column: 2, scope: !200)
!318 = !DILocation(line: 102, column: 1, scope: !200)
!319 = !DILocalVariable(name: "a", arg: 1, scope: !201, file: !1, line: 105, type: !4)
!320 = !DILocation(line: 105, column: 46, scope: !201)
!321 = !DILocalVariable(name: "buff", arg: 2, scope: !201, file: !1, line: 105, type: !43)
!322 = !DILocation(line: 105, column: 61, scope: !201)
!323 = !DILocalVariable(name: "s", arg: 3, scope: !201, file: !1, line: 105, type: !45)
!324 = !DILocation(line: 105, column: 74, scope: !201)
!325 = !DILocalVariable(name: "ret", scope: !201, file: !1, line: 107, type: !23)
!326 = !DILocation(line: 107, column: 6, scope: !201)
!327 = !DILocation(line: 109, column: 31, scope: !201)
!328 = !DILocation(line: 109, column: 34, scope: !201)
!329 = !DILocation(line: 109, column: 40, scope: !201)
!330 = !DILocation(line: 109, column: 8, scope: !201)
!331 = !DILocation(line: 109, column: 6, scope: !201)
!332 = !DILocation(line: 110, column: 6, scope: !333)
!333 = distinct !DILexicalBlock(scope: !201, file: !1, line: 110, column: 6)
!334 = !DILocation(line: 110, column: 10, scope: !333)
!335 = !DILocation(line: 110, column: 6, scope: !201)
!336 = !DILocation(line: 111, column: 11, scope: !333)
!337 = !DILocation(line: 111, column: 3, scope: !333)
!338 = !DILocation(line: 113, column: 11, scope: !333)
!339 = !DILocation(line: 113, column: 10, scope: !333)
!340 = !DILocation(line: 113, column: 3, scope: !333)
!341 = !DILocation(line: 114, column: 1, scope: !201)
!342 = !DILocalVariable(name: "a", arg: 1, scope: !202, file: !1, line: 117, type: !4)
!343 = !DILocation(line: 117, column: 46, scope: !202)
!344 = !DILocalVariable(name: "raw", scope: !202, file: !1, line: 119, type: !192)
!345 = !DILocation(line: 119, column: 14, scope: !202)
!346 = !DILocation(line: 121, column: 22, scope: !202)
!347 = !DILocation(line: 121, column: 25, scope: !202)
!348 = !DILocation(line: 121, column: 8, scope: !202)
!349 = !DILocation(line: 121, column: 6, scope: !202)
!350 = !DILocation(line: 122, column: 7, scope: !202)
!351 = !DILocation(line: 122, column: 2, scope: !202)
!352 = !DILocation(line: 123, column: 2, scope: !202)
!353 = !DILocation(line: 123, column: 5, scope: !202)
!354 = !DILocation(line: 123, column: 17, scope: !202)
!355 = !DILocation(line: 124, column: 2, scope: !202)
