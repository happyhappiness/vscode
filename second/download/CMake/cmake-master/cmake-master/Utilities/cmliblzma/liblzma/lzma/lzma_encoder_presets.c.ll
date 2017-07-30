; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_presets.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }

@lzma_lzma_preset.dict_pow2 = internal constant [10 x i8] c"\12\14\15\16\16\17\17\18\19\1A", align 1
@lzma_lzma_preset.depths = internal constant [4 x i8] c"\04\08\180", align 1

; Function Attrs: nounwind uwtable
define zeroext i8 @lzma_lzma_preset(%struct.lzma_options_lzma* %options, i32 %preset) #0 !dbg !20 {
entry:
  %retval = alloca i8, align 1
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  %preset.addr = alloca i32, align 4
  %level = alloca i32, align 4
  %flags = alloca i32, align 4
  %supported_flags = alloca i32, align 4
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !76, metadata !77), !dbg !78
  store i32 %preset, i32* %preset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %preset.addr, metadata !79, metadata !77), !dbg !80
  call void @llvm.dbg.declare(metadata i32* %level, metadata !81, metadata !77), !dbg !83
  %0 = load i32, i32* %preset.addr, align 4, !dbg !84
  %and = and i32 %0, 31, !dbg !85
  store i32 %and, i32* %level, align 4, !dbg !83
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !86, metadata !77), !dbg !87
  %1 = load i32, i32* %preset.addr, align 4, !dbg !88
  %and1 = and i32 %1, -32, !dbg !89
  store i32 %and1, i32* %flags, align 4, !dbg !87
  call void @llvm.dbg.declare(metadata i32* %supported_flags, metadata !90, metadata !77), !dbg !91
  store i32 -2147483648, i32* %supported_flags, align 4, !dbg !91
  %2 = load i32, i32* %level, align 4, !dbg !92
  %cmp = icmp ugt i32 %2, 9, !dbg !94
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !95

lor.lhs.false:                                    ; preds = %entry
  %3 = load i32, i32* %flags, align 4, !dbg !96
  %and2 = and i32 %3, 2147483647, !dbg !98
  %tobool = icmp ne i32 %and2, 0, !dbg !98
  br i1 %tobool, label %if.then, label %if.end, !dbg !99

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i8 1, i8* %retval, align 1, !dbg !100
  br label %return, !dbg !100

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !101
  %preset_dict = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %4, i32 0, i32 1, !dbg !102
  store i8* null, i8** %preset_dict, align 8, !dbg !103
  %5 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !104
  %preset_dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %5, i32 0, i32 2, !dbg !105
  store i32 0, i32* %preset_dict_size, align 8, !dbg !106
  %6 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !107
  %lc = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %6, i32 0, i32 3, !dbg !108
  store i32 3, i32* %lc, align 4, !dbg !109
  %7 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !110
  %lp = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %7, i32 0, i32 4, !dbg !111
  store i32 0, i32* %lp, align 8, !dbg !112
  %8 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !113
  %pb = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %8, i32 0, i32 5, !dbg !114
  store i32 2, i32* %pb, align 4, !dbg !115
  %9 = load i32, i32* %level, align 4, !dbg !116
  %idxprom = zext i32 %9 to i64, !dbg !117
  %arrayidx = getelementptr inbounds [10 x i8], [10 x i8]* @lzma_lzma_preset.dict_pow2, i64 0, i64 %idxprom, !dbg !117
  %10 = load i8, i8* %arrayidx, align 1, !dbg !117
  %conv = zext i8 %10 to i32, !dbg !117
  %shl = shl i32 1, %conv, !dbg !118
  %11 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !119
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %11, i32 0, i32 0, !dbg !120
  store i32 %shl, i32* %dict_size, align 8, !dbg !121
  %12 = load i32, i32* %level, align 4, !dbg !122
  %cmp3 = icmp ule i32 %12, 3, !dbg !124
  br i1 %cmp3, label %if.then5, label %if.else, !dbg !125

if.then5:                                         ; preds = %if.end
  %13 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !126
  %mode = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %13, i32 0, i32 6, !dbg !128
  store i32 1, i32* %mode, align 8, !dbg !129
  %14 = load i32, i32* %level, align 4, !dbg !130
  %cmp6 = icmp eq i32 %14, 0, !dbg !131
  %cond = select i1 %cmp6, i32 3, i32 4, !dbg !130
  %15 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !132
  %mf = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %15, i32 0, i32 8, !dbg !133
  store i32 %cond, i32* %mf, align 8, !dbg !134
  %16 = load i32, i32* %level, align 4, !dbg !135
  %cmp8 = icmp ule i32 %16, 1, !dbg !136
  %cond10 = select i1 %cmp8, i32 128, i32 273, !dbg !135
  %17 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !137
  %nice_len = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %17, i32 0, i32 7, !dbg !138
  store i32 %cond10, i32* %nice_len, align 4, !dbg !139
  %18 = load i32, i32* %level, align 4, !dbg !140
  %idxprom11 = zext i32 %18 to i64, !dbg !141
  %arrayidx12 = getelementptr inbounds [4 x i8], [4 x i8]* @lzma_lzma_preset.depths, i64 0, i64 %idxprom11, !dbg !141
  %19 = load i8, i8* %arrayidx12, align 1, !dbg !141
  %conv13 = zext i8 %19 to i32, !dbg !141
  %20 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !142
  %depth = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %20, i32 0, i32 9, !dbg !143
  store i32 %conv13, i32* %depth, align 4, !dbg !144
  br label %if.end24, !dbg !145

if.else:                                          ; preds = %if.end
  %21 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !146
  %mode14 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %21, i32 0, i32 6, !dbg !148
  store i32 2, i32* %mode14, align 8, !dbg !149
  %22 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !150
  %mf15 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %22, i32 0, i32 8, !dbg !151
  store i32 20, i32* %mf15, align 8, !dbg !152
  %23 = load i32, i32* %level, align 4, !dbg !153
  %cmp16 = icmp eq i32 %23, 4, !dbg !154
  br i1 %cmp16, label %cond.true, label %cond.false, !dbg !153

cond.true:                                        ; preds = %if.else
  br label %cond.end, !dbg !155

cond.false:                                       ; preds = %if.else
  %24 = load i32, i32* %level, align 4, !dbg !157
  %cmp18 = icmp eq i32 %24, 5, !dbg !159
  %cond20 = select i1 %cmp18, i32 32, i32 64, !dbg !157
  br label %cond.end, !dbg !160

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond21 = phi i32 [ 16, %cond.true ], [ %cond20, %cond.false ], !dbg !161
  %25 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !163
  %nice_len22 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %25, i32 0, i32 7, !dbg !164
  store i32 %cond21, i32* %nice_len22, align 4, !dbg !165
  %26 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !166
  %depth23 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %26, i32 0, i32 9, !dbg !167
  store i32 0, i32* %depth23, align 4, !dbg !168
  br label %if.end24

if.end24:                                         ; preds = %cond.end, %if.then5
  %27 = load i32, i32* %flags, align 4, !dbg !169
  %and25 = and i32 %27, -2147483648, !dbg !171
  %tobool26 = icmp ne i32 %and25, 0, !dbg !171
  br i1 %tobool26, label %if.then27, label %if.end42, !dbg !172

if.then27:                                        ; preds = %if.end24
  %28 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !173
  %mode28 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %28, i32 0, i32 6, !dbg !175
  store i32 2, i32* %mode28, align 8, !dbg !176
  %29 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !177
  %mf29 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %29, i32 0, i32 8, !dbg !178
  store i32 20, i32* %mf29, align 8, !dbg !179
  %30 = load i32, i32* %level, align 4, !dbg !180
  %cmp30 = icmp eq i32 %30, 3, !dbg !182
  br i1 %cmp30, label %if.then35, label %lor.lhs.false32, !dbg !183

lor.lhs.false32:                                  ; preds = %if.then27
  %31 = load i32, i32* %level, align 4, !dbg !184
  %cmp33 = icmp eq i32 %31, 5, !dbg !186
  br i1 %cmp33, label %if.then35, label %if.else38, !dbg !187

if.then35:                                        ; preds = %lor.lhs.false32, %if.then27
  %32 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !188
  %nice_len36 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %32, i32 0, i32 7, !dbg !190
  store i32 192, i32* %nice_len36, align 4, !dbg !191
  %33 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !192
  %depth37 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %33, i32 0, i32 9, !dbg !193
  store i32 0, i32* %depth37, align 4, !dbg !194
  br label %if.end41, !dbg !195

if.else38:                                        ; preds = %lor.lhs.false32
  %34 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !196
  %nice_len39 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %34, i32 0, i32 7, !dbg !198
  store i32 273, i32* %nice_len39, align 4, !dbg !199
  %35 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !200
  %depth40 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %35, i32 0, i32 9, !dbg !201
  store i32 512, i32* %depth40, align 4, !dbg !202
  br label %if.end41

if.end41:                                         ; preds = %if.else38, %if.then35
  br label %if.end42, !dbg !203

if.end42:                                         ; preds = %if.end41, %if.end24
  store i8 0, i8* %retval, align 1, !dbg !204
  br label %return, !dbg !204

return:                                           ; preds = %if.end42, %if.then
  %36 = load i8, i8* %retval, align 1, !dbg !205
  ret i8 %36, !dbg !205
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!73, !74}
!llvm.ident = !{!75}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !19, globals: !64)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_presets.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !8, !15}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 138, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7}
!6 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!7 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!8 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 58, size: 32, align: 32, elements: !9)
!9 = !{!10, !11, !12, !13, !14}
!10 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!11 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!12 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!13 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!14 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!15 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !16, line: 44, size: 32, align: 32, elements: !17)
!16 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!17 = !{!18}
!18 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!19 = !{!20}
!20 = distinct !DISubprogram(name: "lzma_lzma_preset", scope: !1, file: !1, line: 17, type: !21, isLocal: false, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !63)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !25, !30}
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !16, line: 29, baseType: !24)
!24 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!25 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!26 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !4, line: 399, baseType: !27)
!27 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 185, size: 896, align: 64, elements: !28)
!28 = !{!29, !33, !37, !38, !39, !40, !41, !43, !44, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !57, !58, !59, !60, !62}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !27, file: !4, line: 217, baseType: !30, size: 32, align: 32)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !31, line: 51, baseType: !32)
!31 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!32 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !27, file: !4, line: 240, baseType: !34, size: 64, align: 64, offset: 64)
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !36)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !31, line: 48, baseType: !24)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !27, file: !4, line: 254, baseType: !30, size: 32, align: 32, offset: 128)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !27, file: !4, line: 281, baseType: !30, size: 32, align: 32, offset: 160)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !27, file: !4, line: 293, baseType: !30, size: 32, align: 32, offset: 192)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !27, file: !4, line: 316, baseType: !30, size: 32, align: 32, offset: 224)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !27, file: !4, line: 322, baseType: !42, size: 32, align: 32, offset: 256)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !4, line: 155, baseType: !3)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !27, file: !4, line: 342, baseType: !30, size: 32, align: 32, offset: 288)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !27, file: !4, line: 345, baseType: !45, size: 32, align: 32, offset: 320)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !4, line: 111, baseType: !8)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !27, file: !4, line: 375, baseType: !30, size: 32, align: 32, offset: 352)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !27, file: !4, line: 384, baseType: !30, size: 32, align: 32, offset: 384)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !27, file: !4, line: 385, baseType: !30, size: 32, align: 32, offset: 416)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !27, file: !4, line: 386, baseType: !30, size: 32, align: 32, offset: 448)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !27, file: !4, line: 387, baseType: !30, size: 32, align: 32, offset: 480)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !27, file: !4, line: 388, baseType: !30, size: 32, align: 32, offset: 512)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !27, file: !4, line: 389, baseType: !30, size: 32, align: 32, offset: 544)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !27, file: !4, line: 390, baseType: !30, size: 32, align: 32, offset: 576)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !27, file: !4, line: 391, baseType: !30, size: 32, align: 32, offset: 608)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !27, file: !4, line: 392, baseType: !56, size: 32, align: 32, offset: 640)
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !16, line: 46, baseType: !15)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !27, file: !4, line: 393, baseType: !56, size: 32, align: 32, offset: 672)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !27, file: !4, line: 394, baseType: !56, size: 32, align: 32, offset: 704)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !27, file: !4, line: 395, baseType: !56, size: 32, align: 32, offset: 736)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !27, file: !4, line: 396, baseType: !61, size: 64, align: 64, offset: 768)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !27, file: !4, line: 397, baseType: !61, size: 64, align: 64, offset: 832)
!63 = !{}
!64 = !{!65, !69}
!65 = !DIGlobalVariable(name: "dict_pow2", scope: !20, file: !1, line: 19, type: !66, isLocal: true, isDefinition: true, variable: [10 x i8]* @lzma_lzma_preset.dict_pow2)
!66 = !DICompositeType(tag: DW_TAG_array_type, baseType: !35, size: 80, align: 8, elements: !67)
!67 = !{!68}
!68 = !DISubrange(count: 10)
!69 = !DIGlobalVariable(name: "depths", scope: !20, file: !1, line: 21, type: !70, isLocal: true, isDefinition: true, variable: [4 x i8]* @lzma_lzma_preset.depths)
!70 = !DICompositeType(tag: DW_TAG_array_type, baseType: !35, size: 32, align: 8, elements: !71)
!71 = !{!72}
!72 = !DISubrange(count: 4)
!73 = !{i32 2, !"Dwarf Version", i32 4}
!74 = !{i32 2, !"Debug Info Version", i32 3}
!75 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!76 = !DILocalVariable(name: "options", arg: 1, scope: !20, file: !1, line: 17, type: !25)
!77 = !DIExpression()
!78 = !DILocation(line: 17, column: 37, scope: !20)
!79 = !DILocalVariable(name: "preset", arg: 2, scope: !20, file: !1, line: 17, type: !30)
!80 = !DILocation(line: 17, column: 55, scope: !20)
!81 = !DILocalVariable(name: "level", scope: !20, file: !1, line: 23, type: !82)
!82 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !30)
!83 = !DILocation(line: 23, column: 17, scope: !20)
!84 = !DILocation(line: 23, column: 25, scope: !20)
!85 = !DILocation(line: 23, column: 32, scope: !20)
!86 = !DILocalVariable(name: "flags", scope: !20, file: !1, line: 24, type: !82)
!87 = !DILocation(line: 24, column: 17, scope: !20)
!88 = !DILocation(line: 24, column: 25, scope: !20)
!89 = !DILocation(line: 24, column: 32, scope: !20)
!90 = !DILocalVariable(name: "supported_flags", scope: !20, file: !1, line: 25, type: !82)
!91 = !DILocation(line: 25, column: 17, scope: !20)
!92 = !DILocation(line: 27, column: 6, scope: !93)
!93 = distinct !DILexicalBlock(scope: !20, file: !1, line: 27, column: 6)
!94 = !DILocation(line: 27, column: 12, scope: !93)
!95 = !DILocation(line: 27, column: 16, scope: !93)
!96 = !DILocation(line: 27, column: 20, scope: !97)
!97 = !DILexicalBlockFile(scope: !93, file: !1, discriminator: 1)
!98 = !DILocation(line: 27, column: 26, scope: !97)
!99 = !DILocation(line: 27, column: 6, scope: !97)
!100 = !DILocation(line: 28, column: 3, scope: !93)
!101 = !DILocation(line: 30, column: 2, scope: !20)
!102 = !DILocation(line: 30, column: 11, scope: !20)
!103 = !DILocation(line: 30, column: 23, scope: !20)
!104 = !DILocation(line: 31, column: 2, scope: !20)
!105 = !DILocation(line: 31, column: 11, scope: !20)
!106 = !DILocation(line: 31, column: 28, scope: !20)
!107 = !DILocation(line: 33, column: 2, scope: !20)
!108 = !DILocation(line: 33, column: 11, scope: !20)
!109 = !DILocation(line: 33, column: 14, scope: !20)
!110 = !DILocation(line: 34, column: 2, scope: !20)
!111 = !DILocation(line: 34, column: 11, scope: !20)
!112 = !DILocation(line: 34, column: 14, scope: !20)
!113 = !DILocation(line: 35, column: 2, scope: !20)
!114 = !DILocation(line: 35, column: 11, scope: !20)
!115 = !DILocation(line: 35, column: 14, scope: !20)
!116 = !DILocation(line: 37, column: 48, scope: !20)
!117 = !DILocation(line: 37, column: 38, scope: !20)
!118 = !DILocation(line: 37, column: 35, scope: !20)
!119 = !DILocation(line: 37, column: 2, scope: !20)
!120 = !DILocation(line: 37, column: 11, scope: !20)
!121 = !DILocation(line: 37, column: 21, scope: !20)
!122 = !DILocation(line: 39, column: 6, scope: !123)
!123 = distinct !DILexicalBlock(scope: !20, file: !1, line: 39, column: 6)
!124 = !DILocation(line: 39, column: 12, scope: !123)
!125 = !DILocation(line: 39, column: 6, scope: !20)
!126 = !DILocation(line: 40, column: 3, scope: !127)
!127 = distinct !DILexicalBlock(scope: !123, file: !1, line: 39, column: 18)
!128 = !DILocation(line: 40, column: 12, scope: !127)
!129 = !DILocation(line: 40, column: 17, scope: !127)
!130 = !DILocation(line: 41, column: 17, scope: !127)
!131 = !DILocation(line: 41, column: 23, scope: !127)
!132 = !DILocation(line: 41, column: 3, scope: !127)
!133 = !DILocation(line: 41, column: 12, scope: !127)
!134 = !DILocation(line: 41, column: 15, scope: !127)
!135 = !DILocation(line: 42, column: 23, scope: !127)
!136 = !DILocation(line: 42, column: 29, scope: !127)
!137 = !DILocation(line: 42, column: 3, scope: !127)
!138 = !DILocation(line: 42, column: 12, scope: !127)
!139 = !DILocation(line: 42, column: 21, scope: !127)
!140 = !DILocation(line: 43, column: 27, scope: !127)
!141 = !DILocation(line: 43, column: 20, scope: !127)
!142 = !DILocation(line: 43, column: 3, scope: !127)
!143 = !DILocation(line: 43, column: 12, scope: !127)
!144 = !DILocation(line: 43, column: 18, scope: !127)
!145 = !DILocation(line: 44, column: 2, scope: !127)
!146 = !DILocation(line: 45, column: 3, scope: !147)
!147 = distinct !DILexicalBlock(scope: !123, file: !1, line: 44, column: 9)
!148 = !DILocation(line: 45, column: 12, scope: !147)
!149 = !DILocation(line: 45, column: 17, scope: !147)
!150 = !DILocation(line: 46, column: 3, scope: !147)
!151 = !DILocation(line: 46, column: 12, scope: !147)
!152 = !DILocation(line: 46, column: 15, scope: !147)
!153 = !DILocation(line: 47, column: 23, scope: !147)
!154 = !DILocation(line: 47, column: 29, scope: !147)
!155 = !DILocation(line: 47, column: 23, scope: !156)
!156 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 1)
!157 = !DILocation(line: 47, column: 41, scope: !158)
!158 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 2)
!159 = !DILocation(line: 47, column: 47, scope: !158)
!160 = !DILocation(line: 47, column: 23, scope: !158)
!161 = !DILocation(line: 47, column: 23, scope: !162)
!162 = !DILexicalBlockFile(scope: !147, file: !1, discriminator: 3)
!163 = !DILocation(line: 47, column: 3, scope: !162)
!164 = !DILocation(line: 47, column: 12, scope: !162)
!165 = !DILocation(line: 47, column: 21, scope: !162)
!166 = !DILocation(line: 48, column: 3, scope: !147)
!167 = !DILocation(line: 48, column: 12, scope: !147)
!168 = !DILocation(line: 48, column: 18, scope: !147)
!169 = !DILocation(line: 51, column: 6, scope: !170)
!170 = distinct !DILexicalBlock(scope: !20, file: !1, line: 51, column: 6)
!171 = !DILocation(line: 51, column: 12, scope: !170)
!172 = !DILocation(line: 51, column: 6, scope: !20)
!173 = !DILocation(line: 52, column: 3, scope: !174)
!174 = distinct !DILexicalBlock(scope: !170, file: !1, line: 51, column: 35)
!175 = !DILocation(line: 52, column: 12, scope: !174)
!176 = !DILocation(line: 52, column: 17, scope: !174)
!177 = !DILocation(line: 53, column: 3, scope: !174)
!178 = !DILocation(line: 53, column: 12, scope: !174)
!179 = !DILocation(line: 53, column: 15, scope: !174)
!180 = !DILocation(line: 54, column: 7, scope: !181)
!181 = distinct !DILexicalBlock(scope: !174, file: !1, line: 54, column: 7)
!182 = !DILocation(line: 54, column: 13, scope: !181)
!183 = !DILocation(line: 54, column: 18, scope: !181)
!184 = !DILocation(line: 54, column: 21, scope: !185)
!185 = !DILexicalBlockFile(scope: !181, file: !1, discriminator: 1)
!186 = !DILocation(line: 54, column: 27, scope: !185)
!187 = !DILocation(line: 54, column: 7, scope: !185)
!188 = !DILocation(line: 55, column: 4, scope: !189)
!189 = distinct !DILexicalBlock(scope: !181, file: !1, line: 54, column: 33)
!190 = !DILocation(line: 55, column: 13, scope: !189)
!191 = !DILocation(line: 55, column: 22, scope: !189)
!192 = !DILocation(line: 56, column: 4, scope: !189)
!193 = !DILocation(line: 56, column: 13, scope: !189)
!194 = !DILocation(line: 56, column: 19, scope: !189)
!195 = !DILocation(line: 57, column: 3, scope: !189)
!196 = !DILocation(line: 58, column: 4, scope: !197)
!197 = distinct !DILexicalBlock(scope: !181, file: !1, line: 57, column: 10)
!198 = !DILocation(line: 58, column: 13, scope: !197)
!199 = !DILocation(line: 58, column: 22, scope: !197)
!200 = !DILocation(line: 59, column: 4, scope: !197)
!201 = !DILocation(line: 59, column: 13, scope: !197)
!202 = !DILocation(line: 59, column: 19, scope: !197)
!203 = !DILocation(line: 61, column: 2, scope: !174)
!204 = !DILocation(line: 63, column: 2, scope: !20)
!205 = !DILocation(line: 64, column: 1, scope: !20)
