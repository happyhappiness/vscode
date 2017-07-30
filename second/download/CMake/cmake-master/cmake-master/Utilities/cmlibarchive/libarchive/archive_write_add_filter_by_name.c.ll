; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_by_name.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i8*, i32 (%struct.archive*)* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque

@names = internal global [13 x %struct.anon] [%struct.anon { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_b64encode }, %struct.anon { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_bzip2 }, %struct.anon { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.3, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_compress }, %struct.anon { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.4, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_grzip }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_gzip }, %struct.anon { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_lrzip }, %struct.anon { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_lz4 }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_lzip }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_lzma }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.10, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_lzop }, %struct.anon { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.11, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_uuencode }, %struct.anon { i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.12, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_add_filter_xz }, %struct.anon zeroinitializer], align 16
@.str = private unnamed_addr constant [20 x i8] c"No such filter '%s'\00", align 1
@.str.1 = private unnamed_addr constant [10 x i8] c"b64encode\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"bzip2\00", align 1
@.str.3 = private unnamed_addr constant [9 x i8] c"compress\00", align 1
@.str.4 = private unnamed_addr constant [6 x i8] c"grzip\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"gzip\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"lrzip\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"lz4\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"lzip\00", align 1
@.str.9 = private unnamed_addr constant [5 x i8] c"lzma\00", align 1
@.str.10 = private unnamed_addr constant [5 x i8] c"lzop\00", align 1
@.str.11 = private unnamed_addr constant [9 x i8] c"uuencode\00", align 1
@.str.12 = private unnamed_addr constant [3 x i8] c"xz\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_by_name(%struct.archive* %a, i8* %name) #0 !dbg !6 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %name.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !122, metadata !123), !dbg !124
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !125, metadata !123), !dbg !126
  call void @llvm.dbg.declare(metadata i32* %i, metadata !127, metadata !123), !dbg !128
  store i32 0, i32* %i, align 4, !dbg !129
  br label %for.cond, !dbg !131

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !132
  %idxprom = sext i32 %0 to i64, !dbg !135
  %arrayidx = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom, !dbg !135
  %name1 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx, i32 0, i32 0, !dbg !136
  %1 = load i8*, i8** %name1, align 16, !dbg !136
  %cmp = icmp ne i8* %1, null, !dbg !137
  br i1 %cmp, label %for.body, label %for.end, !dbg !138

for.body:                                         ; preds = %for.cond
  %2 = load i8*, i8** %name.addr, align 8, !dbg !139
  %3 = load i32, i32* %i, align 4, !dbg !142
  %idxprom2 = sext i32 %3 to i64, !dbg !143
  %arrayidx3 = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom2, !dbg !143
  %name4 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx3, i32 0, i32 0, !dbg !144
  %4 = load i8*, i8** %name4, align 16, !dbg !144
  %call = call i32 @strcmp(i8* %2, i8* %4) #4, !dbg !145
  %cmp5 = icmp eq i32 %call, 0, !dbg !146
  br i1 %cmp5, label %if.then, label %if.end, !dbg !147

if.then:                                          ; preds = %for.body
  %5 = load i32, i32* %i, align 4, !dbg !148
  %idxprom6 = sext i32 %5 to i64, !dbg !149
  %arrayidx7 = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom6, !dbg !149
  %setter = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx7, i32 0, i32 1, !dbg !150
  %6 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %setter, align 8, !dbg !150
  %7 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !151
  %call8 = call i32 %6(%struct.archive* %7), !dbg !152
  store i32 %call8, i32* %retval, align 4, !dbg !153
  br label %return, !dbg !153

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !154

for.inc:                                          ; preds = %if.end
  %8 = load i32, i32* %i, align 4, !dbg !155
  %inc = add nsw i32 %8, 1, !dbg !155
  store i32 %inc, i32* %i, align 4, !dbg !155
  br label %for.cond, !dbg !157

for.end:                                          ; preds = %for.cond
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !158
  %10 = load i8*, i8** %name.addr, align 8, !dbg !159
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %9, i32 22, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str, i32 0, i32 0), i8* %10), !dbg !160
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !161
  %state = getelementptr inbounds %struct.archive, %struct.archive* %11, i32 0, i32 1, !dbg !162
  store i32 32768, i32* %state, align 4, !dbg !163
  store i32 -30, i32* %retval, align 4, !dbg !164
  br label %return, !dbg !164

return:                                           ; preds = %for.end, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !165
  ret i32 %12, !dbg !165
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

declare i32 @archive_write_add_filter_b64encode(%struct.archive*) #3

declare i32 @archive_write_add_filter_bzip2(%struct.archive*) #3

declare i32 @archive_write_add_filter_compress(%struct.archive*) #3

declare i32 @archive_write_add_filter_grzip(%struct.archive*) #3

declare i32 @archive_write_add_filter_gzip(%struct.archive*) #3

declare i32 @archive_write_add_filter_lrzip(%struct.archive*) #3

declare i32 @archive_write_add_filter_lz4(%struct.archive*) #3

declare i32 @archive_write_add_filter_lzip(%struct.archive*) #3

declare i32 @archive_write_add_filter_lzma(%struct.archive*) #3

declare i32 @archive_write_add_filter_lzop(%struct.archive*) #3

declare i32 @archive_write_add_filter_uuencode(%struct.archive*) #3

declare i32 @archive_write_add_filter_xz(%struct.archive*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!119, !120}
!llvm.ident = !{!121}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5, globals: !110)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_by_name.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6}
!6 = distinct !DISubprogram(name: "archive_write_add_filter_by_name", scope: !1, file: !1, line: 64, type: !7, isLocal: false, isDefinition: true, scopeLine: 65, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !10, !80}
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !12, line: 89, size: 1280, align: 64, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !16, !17, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !11, file: !12, line: 96, baseType: !15, size: 32, align: 32)
!15 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !11, file: !12, line: 97, baseType: !15, size: 32, align: 32, offset: 32)
!17 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !11, file: !12, line: 103, baseType: !18, size: 64, align: 64, offset: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !12, line: 63, size: 832, align: 64, elements: !20)
!20 = !{!21, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !19, file: !12, line: 64, baseType: !22, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DISubroutineType(types: !24)
!24 = !{!9, !10}
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !19, file: !12, line: 65, baseType: !22, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !19, file: !12, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!9, !10, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !19, file: !12, line: 68, baseType: !22, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !19, file: !12, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !10, !43, !45}
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
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !19, file: !12, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !10, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !19, file: !12, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!9, !10, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !19, file: !12, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !19, file: !12, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!9, !10, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !19, file: !12, line: 81, baseType: !22, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !19, file: !12, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !10, !9}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !19, file: !12, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!9, !10, !9}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !19, file: !12, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !10, !9}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !11, file: !12, line: 105, baseType: !9, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !11, file: !12, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !11, file: !12, line: 108, baseType: !9, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !11, file: !12, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !11, file: !12, line: 112, baseType: !9, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !11, file: !12, line: 114, baseType: !9, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !11, file: !12, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !11, file: !12, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !11, file: !12, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !11, file: !12, line: 119, baseType: !15, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !11, file: !12, line: 120, baseType: !15, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !11, file: !12, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !11, file: !12, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !11, file: !12, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !11, file: !12, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !11, file: !12, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !11, file: !12, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !11, file: !12, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !{!111}
!111 = !DIGlobalVariable(name: "names", scope: !0, file: !1, line: 46, type: !112, isLocal: true, isDefinition: true, variable: [13 x %struct.anon]* @names)
!112 = !DICompositeType(tag: DW_TAG_array_type, baseType: !113, size: 1664, align: 64, elements: !117)
!113 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 46, size: 128, align: 64, elements: !114)
!114 = !{!115, !116}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !113, file: !1, line: 46, baseType: !80, size: 64, align: 64)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "setter", scope: !113, file: !1, line: 46, baseType: !22, size: 64, align: 64, offset: 64)
!117 = !{!118}
!118 = !DISubrange(count: 13)
!119 = !{i32 2, !"Dwarf Version", i32 4}
!120 = !{i32 2, !"Debug Info Version", i32 3}
!121 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!122 = !DILocalVariable(name: "a", arg: 1, scope: !6, file: !1, line: 64, type: !10)
!123 = !DIExpression()
!124 = !DILocation(line: 64, column: 50, scope: !6)
!125 = !DILocalVariable(name: "name", arg: 2, scope: !6, file: !1, line: 64, type: !80)
!126 = !DILocation(line: 64, column: 65, scope: !6)
!127 = !DILocalVariable(name: "i", scope: !6, file: !1, line: 66, type: !9)
!128 = !DILocation(line: 66, column: 6, scope: !6)
!129 = !DILocation(line: 68, column: 9, scope: !130)
!130 = distinct !DILexicalBlock(scope: !6, file: !1, line: 68, column: 2)
!131 = !DILocation(line: 68, column: 7, scope: !130)
!132 = !DILocation(line: 68, column: 20, scope: !133)
!133 = !DILexicalBlockFile(scope: !134, file: !1, discriminator: 1)
!134 = distinct !DILexicalBlock(scope: !130, file: !1, line: 68, column: 2)
!135 = !DILocation(line: 68, column: 14, scope: !133)
!136 = !DILocation(line: 68, column: 23, scope: !133)
!137 = !DILocation(line: 68, column: 28, scope: !133)
!138 = !DILocation(line: 68, column: 2, scope: !133)
!139 = !DILocation(line: 69, column: 14, scope: !140)
!140 = distinct !DILexicalBlock(scope: !141, file: !1, line: 69, column: 7)
!141 = distinct !DILexicalBlock(scope: !134, file: !1, line: 68, column: 42)
!142 = !DILocation(line: 69, column: 26, scope: !140)
!143 = !DILocation(line: 69, column: 20, scope: !140)
!144 = !DILocation(line: 69, column: 29, scope: !140)
!145 = !DILocation(line: 69, column: 7, scope: !140)
!146 = !DILocation(line: 69, column: 35, scope: !140)
!147 = !DILocation(line: 69, column: 7, scope: !141)
!148 = !DILocation(line: 70, column: 19, scope: !140)
!149 = !DILocation(line: 70, column: 13, scope: !140)
!150 = !DILocation(line: 70, column: 22, scope: !140)
!151 = !DILocation(line: 70, column: 30, scope: !140)
!152 = !DILocation(line: 70, column: 12, scope: !140)
!153 = !DILocation(line: 70, column: 4, scope: !140)
!154 = !DILocation(line: 71, column: 2, scope: !141)
!155 = !DILocation(line: 68, column: 38, scope: !156)
!156 = !DILexicalBlockFile(scope: !134, file: !1, discriminator: 2)
!157 = !DILocation(line: 68, column: 2, scope: !156)
!158 = !DILocation(line: 73, column: 20, scope: !6)
!159 = !DILocation(line: 73, column: 54, scope: !6)
!160 = !DILocation(line: 73, column: 2, scope: !6)
!161 = !DILocation(line: 74, column: 2, scope: !6)
!162 = !DILocation(line: 74, column: 5, scope: !6)
!163 = !DILocation(line: 74, column: 11, scope: !6)
!164 = !DILocation(line: 75, column: 2, scope: !6)
!165 = !DILocation(line: 76, column: 1, scope: !6)
