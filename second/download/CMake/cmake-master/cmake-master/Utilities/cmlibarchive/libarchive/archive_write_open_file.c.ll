; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_open_file.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.write_FILE_data = type { %struct._IO_FILE* }

@.str = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.1 = private unnamed_addr constant [12 x i8] c"Write error\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_open_FILE(%struct.archive* %a, %struct._IO_FILE* %f) #0 !dbg !72 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %f.addr = alloca %struct._IO_FILE*, align 8
  %mine = alloca %struct.write_FILE_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !93, metadata !94), !dbg !95
  store %struct._IO_FILE* %f, %struct._IO_FILE** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %f.addr, metadata !96, metadata !94), !dbg !97
  call void @llvm.dbg.declare(metadata %struct.write_FILE_data** %mine, metadata !98, metadata !94), !dbg !99
  %call = call noalias i8* @malloc(i64 8) #5, !dbg !100
  %0 = bitcast i8* %call to %struct.write_FILE_data*, !dbg !101
  store %struct.write_FILE_data* %0, %struct.write_FILE_data** %mine, align 8, !dbg !102
  %1 = load %struct.write_FILE_data*, %struct.write_FILE_data** %mine, align 8, !dbg !103
  %cmp = icmp eq %struct.write_FILE_data* %1, null, !dbg !105
  br i1 %cmp, label %if.then, label %if.end, !dbg !106

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !107
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %2, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)), !dbg !109
  store i32 -30, i32* %retval, align 4, !dbg !110
  br label %return, !dbg !110

if.end:                                           ; preds = %entry
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !111
  %4 = load %struct.write_FILE_data*, %struct.write_FILE_data** %mine, align 8, !dbg !112
  %f1 = getelementptr inbounds %struct.write_FILE_data, %struct.write_FILE_data* %4, i32 0, i32 0, !dbg !113
  store %struct._IO_FILE* %3, %struct._IO_FILE** %f1, align 8, !dbg !114
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !115
  %6 = load %struct.write_FILE_data*, %struct.write_FILE_data** %mine, align 8, !dbg !116
  %7 = bitcast %struct.write_FILE_data* %6 to i8*, !dbg !116
  %call2 = call i32 @archive_write_open(%struct.archive* %5, i8* %7, i32 (%struct.archive*, i8*)* @file_open, i64 (%struct.archive*, i8*, i8*, i64)* @file_write, i32 (%struct.archive*, i8*)* @file_close), !dbg !117
  store i32 %call2, i32* %retval, align 4, !dbg !118
  br label %return, !dbg !118

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !119
  ret i32 %8, !dbg !119
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

declare i32 @archive_write_open(%struct.archive*, i8*, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i32 @file_open(%struct.archive* %a, i8* %client_data) #0 !dbg !78 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !120, metadata !94), !dbg !121
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !122, metadata !94), !dbg !123
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !124
  %1 = load i8*, i8** %client_data.addr, align 8, !dbg !125
  ret i32 0, !dbg !126
}

; Function Attrs: nounwind uwtable
define internal i64 @file_write(%struct.archive* %a, i8* %client_data, i8* %buff, i64 %length) #0 !dbg !81 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %mine = alloca %struct.write_FILE_data*, align 8
  %bytesWritten = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !127, metadata !94), !dbg !128
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !129, metadata !94), !dbg !130
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !131, metadata !94), !dbg !132
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !133, metadata !94), !dbg !134
  call void @llvm.dbg.declare(metadata %struct.write_FILE_data** %mine, metadata !135, metadata !94), !dbg !136
  call void @llvm.dbg.declare(metadata i64* %bytesWritten, metadata !137, metadata !94), !dbg !138
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !139
  %1 = bitcast i8* %0 to %struct.write_FILE_data*, !dbg !139
  store %struct.write_FILE_data* %1, %struct.write_FILE_data** %mine, align 8, !dbg !140
  br label %for.cond, !dbg !141

for.cond:                                         ; preds = %if.then3, %entry
  %2 = load i8*, i8** %buff.addr, align 8, !dbg !142
  %3 = load i64, i64* %length.addr, align 8, !dbg !146
  %4 = load %struct.write_FILE_data*, %struct.write_FILE_data** %mine, align 8, !dbg !147
  %f = getelementptr inbounds %struct.write_FILE_data, %struct.write_FILE_data* %4, i32 0, i32 0, !dbg !148
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** %f, align 8, !dbg !148
  %call = call i64 @fwrite(i8* %2, i64 1, i64 %3, %struct._IO_FILE* %5), !dbg !149
  store i64 %call, i64* %bytesWritten, align 8, !dbg !150
  %6 = load i64, i64* %bytesWritten, align 8, !dbg !151
  %cmp = icmp ule i64 %6, 0, !dbg !153
  br i1 %cmp, label %if.then, label %if.end5, !dbg !154

if.then:                                          ; preds = %for.cond
  %call1 = call i32* @__errno_location() #1, !dbg !155
  %7 = load i32, i32* %call1, align 4, !dbg !155
  %cmp2 = icmp eq i32 %7, 4, !dbg !158
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !159

if.then3:                                         ; preds = %if.then
  br label %for.cond, !dbg !160

if.end:                                           ; preds = %if.then
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !161
  %call4 = call i32* @__errno_location() #1, !dbg !162
  %9 = load i32, i32* %call4, align 4, !dbg !162
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %8, i32 %9, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i32 0, i32 0)), !dbg !163
  store i64 -1, i64* %retval, align 8, !dbg !165
  br label %return, !dbg !165

if.end5:                                          ; preds = %for.cond
  %10 = load i64, i64* %bytesWritten, align 8, !dbg !166
  store i64 %10, i64* %retval, align 8, !dbg !167
  br label %return, !dbg !167

return:                                           ; preds = %if.end5, %if.end
  %11 = load i64, i64* %retval, align 8, !dbg !168
  ret i64 %11, !dbg !168
}

; Function Attrs: nounwind uwtable
define internal i32 @file_close(%struct.archive* %a, i8* %client_data) #0 !dbg !89 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %mine = alloca %struct.write_FILE_data*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !169, metadata !94), !dbg !170
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !171, metadata !94), !dbg !172
  call void @llvm.dbg.declare(metadata %struct.write_FILE_data** %mine, metadata !173, metadata !94), !dbg !174
  %0 = load i8*, i8** %client_data.addr, align 8, !dbg !175
  %1 = bitcast i8* %0 to %struct.write_FILE_data*, !dbg !175
  store %struct.write_FILE_data* %1, %struct.write_FILE_data** %mine, align 8, !dbg !174
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !176
  %3 = load %struct.write_FILE_data*, %struct.write_FILE_data** %mine, align 8, !dbg !177
  %4 = bitcast %struct.write_FILE_data* %3 to i8*, !dbg !177
  call void @free(i8* %4) #5, !dbg !178
  ret i32 0, !dbg !179
}

declare i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind
declare void @free(i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!90, !91}
!llvm.ident = !{!92}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !71)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_open_file.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !58}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "write_FILE_data", file: !1, line: 50, size: 64, align: 64, elements: !6)
!6 = !{!7}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "f", scope: !5, file: !1, line: 51, baseType: !8, size: 64, align: 64)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !10, line: 48, baseType: !11)
!10 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !12, line: 245, size: 1728, align: 64, elements: !13)
!12 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !16, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !37, !38, !39, !40, !44, !46, !48, !52, !55, !57, !59, !60, !61, !62, !66, !67}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !11, file: !12, line: 246, baseType: !15, size: 32, align: 32)
!15 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !11, file: !12, line: 251, baseType: !17, size: 64, align: 64, offset: 64)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !11, file: !12, line: 252, baseType: !17, size: 64, align: 64, offset: 128)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !11, file: !12, line: 253, baseType: !17, size: 64, align: 64, offset: 192)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !11, file: !12, line: 254, baseType: !17, size: 64, align: 64, offset: 256)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !11, file: !12, line: 255, baseType: !17, size: 64, align: 64, offset: 320)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !11, file: !12, line: 256, baseType: !17, size: 64, align: 64, offset: 384)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !11, file: !12, line: 257, baseType: !17, size: 64, align: 64, offset: 448)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !11, file: !12, line: 258, baseType: !17, size: 64, align: 64, offset: 512)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !11, file: !12, line: 260, baseType: !17, size: 64, align: 64, offset: 576)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !11, file: !12, line: 261, baseType: !17, size: 64, align: 64, offset: 640)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !11, file: !12, line: 262, baseType: !17, size: 64, align: 64, offset: 704)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !11, file: !12, line: 264, baseType: !30, size: 64, align: 64, offset: 768)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !12, line: 160, size: 192, align: 64, elements: !32)
!32 = !{!33, !34, !36}
!33 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !31, file: !12, line: 161, baseType: !30, size: 64, align: 64)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !31, file: !12, line: 162, baseType: !35, size: 64, align: 64, offset: 64)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !31, file: !12, line: 166, baseType: !15, size: 32, align: 32, offset: 128)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !11, file: !12, line: 266, baseType: !35, size: 64, align: 64, offset: 832)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !11, file: !12, line: 268, baseType: !15, size: 32, align: 32, offset: 896)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !11, file: !12, line: 272, baseType: !15, size: 32, align: 32, offset: 928)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !11, file: !12, line: 274, baseType: !41, size: 64, align: 64, offset: 960)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !42, line: 131, baseType: !43)
!42 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!43 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !11, file: !12, line: 278, baseType: !45, size: 16, align: 16, offset: 1024)
!45 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !11, file: !12, line: 279, baseType: !47, size: 8, align: 8, offset: 1040)
!47 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !11, file: !12, line: 280, baseType: !49, size: 8, align: 8, offset: 1048)
!49 = !DICompositeType(tag: DW_TAG_array_type, baseType: !18, size: 8, align: 8, elements: !50)
!50 = !{!51}
!51 = !DISubrange(count: 1)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !11, file: !12, line: 284, baseType: !53, size: 64, align: 64, offset: 1088)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !12, line: 154, baseType: null)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !11, file: !12, line: 293, baseType: !56, size: 64, align: 64, offset: 1152)
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !42, line: 132, baseType: !43)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !11, file: !12, line: 302, baseType: !58, size: 64, align: 64, offset: 1216)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !11, file: !12, line: 303, baseType: !58, size: 64, align: 64, offset: 1280)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !11, file: !12, line: 304, baseType: !58, size: 64, align: 64, offset: 1344)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !11, file: !12, line: 305, baseType: !58, size: 64, align: 64, offset: 1408)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !11, file: !12, line: 306, baseType: !63, size: 64, align: 64, offset: 1472)
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !64, line: 62, baseType: !65)
!64 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!65 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !11, file: !12, line: 308, baseType: !15, size: 32, align: 32, offset: 1536)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !11, file: !12, line: 310, baseType: !68, size: 160, align: 8, offset: 1568)
!68 = !DICompositeType(tag: DW_TAG_array_type, baseType: !18, size: 160, align: 8, elements: !69)
!69 = !{!70}
!70 = !DISubrange(count: 20)
!71 = !{!72, !78, !81, !89}
!72 = distinct !DISubprogram(name: "archive_write_open_FILE", scope: !1, file: !1, line: 59, type: !73, isLocal: false, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!73 = !DISubroutineType(types: !74)
!74 = !{!15, !75, !8}
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !77, line: 179, flags: DIFlagFwdDecl)
!77 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!78 = distinct !DISubprogram(name: "file_open", scope: !1, file: !1, line: 74, type: !79, isLocal: true, isDefinition: true, scopeLine: 75, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!79 = !DISubroutineType(types: !80)
!80 = !{!15, !75, !58}
!81 = distinct !DISubprogram(name: "file_write", scope: !1, file: !1, line: 83, type: !82, isLocal: true, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!82 = !DISubroutineType(types: !83)
!83 = !{!84, !75, !58, !87, !63}
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !85, line: 109, baseType: !86)
!85 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !42, line: 172, baseType: !43)
!87 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!88 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!89 = distinct !DISubprogram(name: "file_close", scope: !1, file: !1, line: 102, type: !79, isLocal: true, isDefinition: true, scopeLine: 103, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!90 = !{i32 2, !"Dwarf Version", i32 4}
!91 = !{i32 2, !"Debug Info Version", i32 3}
!92 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!93 = !DILocalVariable(name: "a", arg: 1, scope: !72, file: !1, line: 59, type: !75)
!94 = !DIExpression()
!95 = !DILocation(line: 59, column: 41, scope: !72)
!96 = !DILocalVariable(name: "f", arg: 2, scope: !72, file: !1, line: 59, type: !8)
!97 = !DILocation(line: 59, column: 50, scope: !72)
!98 = !DILocalVariable(name: "mine", scope: !72, file: !1, line: 61, type: !4)
!99 = !DILocation(line: 61, column: 26, scope: !72)
!100 = !DILocation(line: 63, column: 35, scope: !72)
!101 = !DILocation(line: 63, column: 9, scope: !72)
!102 = !DILocation(line: 63, column: 7, scope: !72)
!103 = !DILocation(line: 64, column: 6, scope: !104)
!104 = distinct !DILexicalBlock(scope: !72, file: !1, line: 64, column: 6)
!105 = !DILocation(line: 64, column: 11, scope: !104)
!106 = !DILocation(line: 64, column: 6, scope: !72)
!107 = !DILocation(line: 65, column: 21, scope: !108)
!108 = distinct !DILexicalBlock(scope: !104, file: !1, line: 64, column: 20)
!109 = !DILocation(line: 65, column: 3, scope: !108)
!110 = !DILocation(line: 66, column: 3, scope: !108)
!111 = !DILocation(line: 68, column: 12, scope: !72)
!112 = !DILocation(line: 68, column: 2, scope: !72)
!113 = !DILocation(line: 68, column: 8, scope: !72)
!114 = !DILocation(line: 68, column: 10, scope: !72)
!115 = !DILocation(line: 69, column: 29, scope: !72)
!116 = !DILocation(line: 69, column: 32, scope: !72)
!117 = !DILocation(line: 69, column: 10, scope: !72)
!118 = !DILocation(line: 69, column: 2, scope: !72)
!119 = !DILocation(line: 71, column: 1, scope: !72)
!120 = !DILocalVariable(name: "a", arg: 1, scope: !78, file: !1, line: 74, type: !75)
!121 = !DILocation(line: 74, column: 27, scope: !78)
!122 = !DILocalVariable(name: "client_data", arg: 2, scope: !78, file: !1, line: 74, type: !58)
!123 = !DILocation(line: 74, column: 36, scope: !78)
!124 = !DILocation(line: 76, column: 8, scope: !78)
!125 = !DILocation(line: 77, column: 8, scope: !78)
!126 = !DILocation(line: 79, column: 2, scope: !78)
!127 = !DILocalVariable(name: "a", arg: 1, scope: !81, file: !1, line: 83, type: !75)
!128 = !DILocation(line: 83, column: 28, scope: !81)
!129 = !DILocalVariable(name: "client_data", arg: 2, scope: !81, file: !1, line: 83, type: !58)
!130 = !DILocation(line: 83, column: 37, scope: !81)
!131 = !DILocalVariable(name: "buff", arg: 3, scope: !81, file: !1, line: 83, type: !87)
!132 = !DILocation(line: 83, column: 62, scope: !81)
!133 = !DILocalVariable(name: "length", arg: 4, scope: !81, file: !1, line: 83, type: !63)
!134 = !DILocation(line: 83, column: 75, scope: !81)
!135 = !DILocalVariable(name: "mine", scope: !81, file: !1, line: 85, type: !4)
!136 = !DILocation(line: 85, column: 26, scope: !81)
!137 = !DILocalVariable(name: "bytesWritten", scope: !81, file: !1, line: 86, type: !63)
!138 = !DILocation(line: 86, column: 9, scope: !81)
!139 = !DILocation(line: 88, column: 9, scope: !81)
!140 = !DILocation(line: 88, column: 7, scope: !81)
!141 = !DILocation(line: 89, column: 2, scope: !81)
!142 = !DILocation(line: 90, column: 25, scope: !143)
!143 = distinct !DILexicalBlock(scope: !144, file: !1, line: 89, column: 11)
!144 = distinct !DILexicalBlock(scope: !145, file: !1, line: 89, column: 2)
!145 = distinct !DILexicalBlock(scope: !81, file: !1, line: 89, column: 2)
!146 = !DILocation(line: 90, column: 34, scope: !143)
!147 = !DILocation(line: 90, column: 42, scope: !143)
!148 = !DILocation(line: 90, column: 48, scope: !143)
!149 = !DILocation(line: 90, column: 18, scope: !143)
!150 = !DILocation(line: 90, column: 16, scope: !143)
!151 = !DILocation(line: 91, column: 7, scope: !152)
!152 = distinct !DILexicalBlock(scope: !143, file: !1, line: 91, column: 7)
!153 = !DILocation(line: 91, column: 20, scope: !152)
!154 = !DILocation(line: 91, column: 7, scope: !143)
!155 = !DILocation(line: 92, column: 8, scope: !156)
!156 = distinct !DILexicalBlock(scope: !157, file: !1, line: 92, column: 8)
!157 = distinct !DILexicalBlock(scope: !152, file: !1, line: 91, column: 26)
!158 = !DILocation(line: 92, column: 14, scope: !156)
!159 = !DILocation(line: 92, column: 8, scope: !157)
!160 = !DILocation(line: 93, column: 5, scope: !156)
!161 = !DILocation(line: 94, column: 22, scope: !157)
!162 = !DILocation(line: 94, column: 25, scope: !157)
!163 = !DILocation(line: 94, column: 4, scope: !164)
!164 = !DILexicalBlockFile(scope: !157, file: !1, discriminator: 1)
!165 = !DILocation(line: 95, column: 4, scope: !157)
!166 = !DILocation(line: 97, column: 11, scope: !143)
!167 = !DILocation(line: 97, column: 3, scope: !143)
!168 = !DILocation(line: 99, column: 1, scope: !81)
!169 = !DILocalVariable(name: "a", arg: 1, scope: !89, file: !1, line: 102, type: !75)
!170 = !DILocation(line: 102, column: 28, scope: !89)
!171 = !DILocalVariable(name: "client_data", arg: 2, scope: !89, file: !1, line: 102, type: !58)
!172 = !DILocation(line: 102, column: 37, scope: !89)
!173 = !DILocalVariable(name: "mine", scope: !89, file: !1, line: 104, type: !4)
!174 = !DILocation(line: 104, column: 26, scope: !89)
!175 = !DILocation(line: 104, column: 33, scope: !89)
!176 = !DILocation(line: 106, column: 8, scope: !89)
!177 = !DILocation(line: 107, column: 7, scope: !89)
!178 = !DILocation(line: 107, column: 2, scope: !89)
!179 = !DILocation(line: 108, column: 2, scope: !89)
